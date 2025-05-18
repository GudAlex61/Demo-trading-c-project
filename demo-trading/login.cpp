#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "sql.h"
#include "sqlite3.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString login = ui->log->text();
    QString password = ui->pass->text();

    AuthManager Users("UserDB");
    int userId;
    double balance;

    if (Users.loginUser(login.toStdString(), password.toStdString(), balance, userId)){
        hide();
        MainWindow *mainWindow = new MainWindow(userId, balance);
        mainWindow->show();
        
    }
    else{
        QMessageBox::critical(this, "", "Ваш аккаунт заблокирован, предоставьте договор с мобильным оператором");
    }
}
