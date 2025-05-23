#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QMainWindow>
#include "login.h"
#include "registration.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Authorization;
}
QT_END_NAMESPACE

class Authorization : public QMainWindow
{
    Q_OBJECT

public:
    Authorization(QWidget *parent = nullptr);
    ~Authorization();

private slots:
    void on_pushButton_clicked();
    void on_regButton_clicked();

private:
    Ui::Authorization *ui;
    login *logWindow;
    Registration *regWindow;
};
#endif // AUTHORIZATION_H
