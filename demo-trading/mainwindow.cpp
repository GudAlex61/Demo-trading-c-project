#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "api.h"
#include "sql.h"
#include <QStandardItemModel>
#include <QColor>

MainWindow::MainWindow(int userId, double balance, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), 
      balance(balance), userId(userId), model(nullptr)
{
    ui->setupUi(this);
    
    ui->tradesView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tradesView->horizontalHeader()->setVisible(false);
    ui->tradesView->verticalHeader()->setVisible(false);

    connect(ui->tradesView, &QTableView::clicked, this, &MainWindow::onTradeClicked);

    webView = new QWebEngineView(this);
    webView->setGeometry(30, 390, 740, 240);

    connect(ui->comboBox, &QComboBox::currentTextChanged, 
            this, &MainWindow::onCryptoSelected);
    onCryptoSelected(ui->comboBox->currentText());

    auto activateButton = [this]() {
        ui->addTradeButton->setEnabled(
            ui->longRadio->isChecked() || ui->shortRadio->isChecked()
        );
    };

    connect(ui->longRadio, &QRadioButton::toggled, this, activateButton);
    connect(ui->shortRadio, &QRadioButton::toggled, this, activateButton);

    connect(ui->longRadio, &QRadioButton::clicked, [this]() {
        ui->addTradeButton->setStyleSheet(
            "QPushButton { background: #4CAF50; color: white; }"
        );
    });

    connect(ui->shortRadio, &QRadioButton::clicked, [this]() {
        ui->addTradeButton->setStyleSheet(
            "QPushButton { background: #F44336; color: white; }"
        );
    });

    AuthManager Users("UserDB");
    ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));
    Users.getTrades(userId, positions);
    on_uploadButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCryptoSelected(const QString& selectedCrypto) {
    QString symbol = selectedCrypto + "USDT";
    loadTradingViewChart(symbol);
}

void MainWindow::loadTradingViewChart(const QString& symbol) {
    QString html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <style>
                body { margin: 0; padding: 0; }
                #tradingview_chart { height: 300px; }
            </style>
            <script type="text/javascript" src="https://s3.tradingview.com/tv.js"></script>
        </head>
        <body>
        <div id="tradingview_chart"></div>
        <script>
            new TradingView.widget({
                "autosize": true,
                "symbol": "BINANCE:)" + symbol + R"(",
                "interval": "D",
                "timezone": "Etc/UTC",
                "theme": "light",
                "style": "1",
                "locale": "ru",
                "hide_side_toolbar": false,
                "allow_symbol_change": true,
                "container_id": "tradingview_chart"
            });
        </script>
        </body>
        </html>
    )";

    webView->setHtml(html);
}

void MainWindow::on_addTradeButton_clicked() {
    if (!ui->longRadio->isChecked() && !ui->shortRadio->isChecked()) {
        QMessageBox::warning(this, "Ошибка", "Выберите тип позиции (LONG/SHORT)!");
        return;
    }

    bool isLong = ui->longRadio->isChecked();

    QString cryptoID = ui->comboBox->currentText();
    int leverage = ui->spinBox->value();
    double amount = ui->amountSpinBox->value();

    if (amount <= 0 || amount > balance) {
        QMessageBox::critical(this, "Ошибка", "Некорректная сумма!");
        return;
    }

    try {
        Position newPosition = MakingPosition(cryptoID.toStdString(), isLong, leverage, amount);
        positions.push_back(newPosition);
        
        balance -= amount;
        ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));

        AuthManager users("UserDB");
        users.saveTrades(userId, positions);
        users.saveBalance(userId, balance);

        on_uploadButton_clicked();

        QMessageBox::information(this, "Успех", "Позиция успешно создана!");

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", 
            QString("Ошибка при создании позиции:\n%1").arg(e.what()));
    }
}
void MainWindow::on_uploadButton_clicked()
{
    for (int i = positions.size() - 1; i >= 0; --i) {
        if (checkLiquidation(positions[i])) {
            QMessageBox::critical(this, "Ликвидирована позиция", "");
            positions.erase(positions.begin() + i);
        }
    }

    if (model) {
        delete model;
        model = nullptr;
    }

    model = new QStandardItemModel(positions.size(), 4, this);

    for (int i = 0; i < positions.size(); i++) {
        Position& position = positions[i];
        QString name = QString::fromStdString(position.getTokenName());
        QString leverage = QString::number(position.getShoulder());
        QString price = QString::number(position.getEntryPrice(), 'f', 2);
        QString myMargin = QString::number(position.getMargin(), 'f', 2);
        QString pnl = QString::number(position.calculatePnL(), 'f', 2);
        QString los = position.getIsLong() ? "LONG" : "SHORT";

        ui->tradesView->setRowHeight(i, 60);

        QStandardItem* typeItem = new QStandardItem("          " + los + " " + name + "\n               х" + leverage);
        QStandardItem* priceItem = new QStandardItem("$" + price + "\n$" + myMargin);
        QStandardItem* pnlItem = new QStandardItem("$" + pnl);

        QColor mainColor = position.getIsLong() ? QColor("#4CAF50") : QColor("#F44336");
        typeItem->setForeground(mainColor);
        QColor pnlColor = (position.calculatePnL() >= 0) ? QColor("#4CAF50") : QColor("#F44336");
        pnlItem->setForeground(pnlColor);

        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        pnlItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        model->setItem(i, 0, typeItem);
        model->setItem(i, 1, priceItem);
        model->setItem(i, 2, pnlItem);

        QStandardItem* closeItem = new QStandardItem("×");
        closeItem->setTextAlignment(Qt::AlignCenter);
        closeItem->setEditable(false);
        model->setItem(i, 3, closeItem);

    }

    ui->tradesView->verticalHeader()->setVisible(false);
    ui->tradesView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tradesView->setModel(model);

    ui->tradesView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tradesView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tradesView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tradesView->setColumnWidth(0, 160);
    ui->tradesView->setColumnWidth(1, 160);
    ui->tradesView->setColumnWidth(2, 160);
    ui->tradesView->horizontalHeader()->setStretchLastSection(true);

    // ui->tradesView->setShowGrid(false);
    ui->tradesView->setStyleSheet(
        "QTableView::item { border-bottom: 1px solid #EEEEEE; }"
    );
}

void MainWindow::onTradeClicked(const QModelIndex &index)
{
    if(index.column() == 3) {
        int row = index.row();
        if(row >= 0 && row < positions.size()) {
            balance += positions[row].getMargin() + positions[row].calculatePnL();
            positions.erase(positions.begin() + row);
            
            AuthManager Users("UserDB");
            Users.saveTrades(userId, positions);
            Users.saveBalance(userId, balance);
            
            on_uploadButton_clicked();
            ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));
        }
    }
}
