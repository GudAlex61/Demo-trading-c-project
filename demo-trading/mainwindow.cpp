#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "api.h"
#include "sql.h"

MainWindow::MainWindow(int userId, double balance, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , balance(balance)
    , userId(userId)
{
    AuthManager Users("UserDB");

    ui->setupUi(this);
    ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));

    Users.getTrades(userId, positions);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTradeButton_clicked()
{
    bool isLong;
    if(ui->longRadio->isChecked()) {
        isLong = true;
    } else if(ui->shortRadio->isChecked()) {
        isLong = false;
    } else {
        return;
    }

    QString cryptoID = ui->comboBox->currentText();

    int leverage = ui->spinBox->value();

    double amount = ui->amountSpinBox->value();

    if (amount > balance){
        QMessageBox::critical(this, "", "У вас недостаточно средств!");
    }
    else {
        positions.push_back(MakingPosition(cryptoID.toStdString(), isLong, leverage, amount));
        QMessageBox::information(this, "", "Позиция добавлена");
        balance -= amount;
        ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));

        AuthManager Users("UserDB");

        Users.saveTrades(userId, positions);
        Users.saveBalance(userId, balance);
    }
}

void MainWindow::on_uploadButton_clicked()
{
    for (int i = 0; i < positions.size(); i++){
                Position position = positions[i];
                if (checkLiquidation(position)){
                    QMessageBox::critical(this, "Ликвидирована позиция", "");
                    positions.erase(positions.begin()+i);
                }
    }
    model = new QStandardItemModel(positions.size(), 3, this);

    for (int i = 0; i < positions.size(); i++){
        Position position = positions[i];
        QString name = QString::fromStdString(position.getTokenName());
        QString leverage = QString::number(position.getShoulder());
        QString price = QString::number(position.getEntryPrice());
        QString myMargin = QString::number(position.getMargin());
        QString pnl = QString::number(position.calculatePnL(position));
        QString los;
        if (position.getIsLong()) {
            los = "LONG";
        }
        else {
            los = "SHORT";
        }

        model->setItem(i, 0, new QStandardItem(los + " " + name + "\n х" + leverage + " плечо"));
        model->setItem(i, 1, new QStandardItem("$" + price + "\n$" + myMargin));
        model->setItem(i, 2, new QStandardItem("$" + pnl));
    }

    ui->tradesView->setModel(model);
    ui->tradesView->resizeColumnsToContents();
}
