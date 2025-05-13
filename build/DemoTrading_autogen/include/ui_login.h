/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *log;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *pass;
    QPushButton *pushButton;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(400, 600);
        groupBox = new QGroupBox(login);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(100, 240, 200, 120));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        log = new QLineEdit(groupBox);
        log->setObjectName("log");

        horizontalLayout->addWidget(log);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        pass = new QLineEdit(groupBox);
        pass->setObjectName("pass");

        horizontalLayout_2->addWidget(pass);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Demo-Trading", nullptr));
        groupBox->setTitle(QCoreApplication::translate("login", "\320\222\321\205\320\276\320\264", nullptr));
        label->setText(QCoreApplication::translate("login", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        log->setText(QString());
        label_2->setText(QCoreApplication::translate("login", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("login", "\320\222\320\276\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
