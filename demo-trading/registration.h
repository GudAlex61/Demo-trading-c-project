#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_regButton_clicked();

    void on_backButton_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
