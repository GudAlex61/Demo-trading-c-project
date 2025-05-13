#include "authorization.h"
#include "./ui_authorization.h"
#include "sql.h"
#include "sqlite3.h"

Authorization::Authorization(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_pushButton_clicked()
{
    hide();
    logWindow = new login(this);
    logWindow->show();
}


void Authorization::on_regButton_clicked()
{
    hide();
    regWindow = new Registration(this);
    regWindow->show();
}

