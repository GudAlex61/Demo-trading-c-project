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

    double amount = ui->sumEdit->text().replace(",", ".").toDouble();

    if (amount > balance){
        return;
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



