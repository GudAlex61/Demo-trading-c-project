/********************************************************************************
** Form generated from reading UI file 'authorization.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATION_H
#define UI_AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Authorization
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *regButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Authorization)
    {
        if (Authorization->objectName().isEmpty())
            Authorization->setObjectName("Authorization");
        Authorization->resize(400, 600);
        Authorization->setStyleSheet(QString::fromUtf8("background-color: white;"));
        centralwidget = new QWidget(Authorization);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(100, 243, 200, 121));
        groupBox->setStyleSheet(QString::fromUtf8("\n"
"            QGroupBox {\n"
"              border: 1px solid #E0E0E0;\n"
"              border-radius: 8px;\n"
"              margin-top: 0px;\n"
"              padding-top: 25px;\n"
"              font: bold 12pt \"Segoe UI\";\n"
"              color: black;\n"
"              background: white;\n"
"            }\n"
"            QGroupBox::title {\n"
"			 subcontrol-origin: margin;\n"
"              left: 5px;\n"
"			 top: 5px;\n"
"            }"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 30, 171, 76));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("padding: 8px 10px;\n"
"font-size: 10pt;\n"
"color: black;"));

        verticalLayout->addWidget(pushButton);

        regButton = new QPushButton(layoutWidget);
        regButton->setObjectName("regButton");
        regButton->setStyleSheet(QString::fromUtf8("padding: 8px 10px;\n"
"font-size: 10pt;\n"
"color: black;"));

        verticalLayout->addWidget(regButton);

        Authorization->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Authorization);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 23));
        Authorization->setMenuBar(menubar);
        statusbar = new QStatusBar(Authorization);
        statusbar->setObjectName("statusbar");
        Authorization->setStatusBar(statusbar);

        retranslateUi(Authorization);

        QMetaObject::connectSlotsByName(Authorization);
    } // setupUi

    void retranslateUi(QMainWindow *Authorization)
    {
        Authorization->setWindowTitle(QCoreApplication::translate("Authorization", "Demo-Trading", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Authorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        pushButton->setText(QCoreApplication::translate("Authorization", "\320\222\321\205\320\276\320\264", nullptr));
        regButton->setText(QCoreApplication::translate("Authorization", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authorization: public Ui_Authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
