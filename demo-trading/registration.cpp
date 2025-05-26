#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
#include "sql.h"
#include "sqlite3.h"
#include "authorization.h"

Registration::Registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_regButton_clicked()
{
    QString login = ui->loginLine->text();
    QString password = ui->passLine->text();
    QString secPassword = ui->secpassLine->text();

    AuthManager Users("UserDB");
    int UserId;
    double balance;

    if (password != secPassword) {
        QMessageBox::critical(this, "", "Пароли не совпадают, попробуйте еще раз");
    }

    else if (Users.registerUser(login.toStdString(), password.toStdString(), balance, UserId)) {
        hide();
        MainWindow *mainWindow = new MainWindow(UserId, balance);
        mainWindow->show();
    }

    else {
        QMessageBox::critical(this, "", "Произошла ошибка. Логин уже используется.");
    }
}



void Registration::on_backButton_clicked()
{
    hide();
    Authorization *authWindow = new Authorization();
    authWindow->show();
}

