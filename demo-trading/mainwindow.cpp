#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const int userId, double balance, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , balance(balance)
    , userId(userId)
{
    ui->setupUi(this);
    ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    balance -= 1000;
    ui->statusbar->showMessage(QString("Баланс: %1").arg(balance));
}



