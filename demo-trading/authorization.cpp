#include "authorization.h"
#include "./ui_authorization.h"
#include "/home/greg_goozmer/i_love_dasha/Demo-trading-c-project/include/sql.h"
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


void Authorization::on_pushButton_2_clicked()
{

}
