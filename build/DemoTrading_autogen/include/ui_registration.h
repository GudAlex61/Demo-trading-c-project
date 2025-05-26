/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QGroupBox *regBox;
    QPushButton *backButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *loginLine;
    QLineEdit *passLine;
    QLineEdit *secpassLine;
    QPushButton *regButton;

    void setupUi(QDialog *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName("Registration");
        Registration->resize(400, 600);
        Registration->setStyleSheet(QString::fromUtf8("background-color: white;"));
        regBox = new QGroupBox(Registration);
        regBox->setObjectName("regBox");
        regBox->setGeometry(QRect(60, 225, 281, 171));
        regBox->setStyleSheet(QString::fromUtf8("\n"
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
        backButton = new QPushButton(regBox);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(230, 5, 31, 21));
        backButton->setStyleSheet(QString::fromUtf8("            QPushButton {\n"
"              background: #E0E0E0;\n"
"              color: #616161;\n"
"              border-radius: 6px;\n"
"              font: bold 12pt \"Segoe UI\";\n"
"            }\n"
"            QPushButton:hover {\n"
"              background: #BDBDBD;\n"
"            }"));
        layoutWidget = new QWidget(regBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 35, 256, 136));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color: black;"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: black;"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("border-radius: 3px;\n"
"color: black;"));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        loginLine = new QLineEdit(layoutWidget);
        loginLine->setObjectName("loginLine");
        loginLine->setStyleSheet(QString::fromUtf8("color: black;"));
        loginLine->setMaxLength(12);

        verticalLayout_2->addWidget(loginLine);

        passLine = new QLineEdit(layoutWidget);
        passLine->setObjectName("passLine");
        passLine->setStyleSheet(QString::fromUtf8("color: black;"));
        passLine->setMaxLength(12);

        verticalLayout_2->addWidget(passLine);

        secpassLine = new QLineEdit(layoutWidget);
        secpassLine->setObjectName("secpassLine");
        secpassLine->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"color: black;"));
        secpassLine->setMaxLength(12);

        verticalLayout_2->addWidget(secpassLine);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        regButton = new QPushButton(layoutWidget);
        regButton->setObjectName("regButton");
        regButton->setStyleSheet(QString::fromUtf8("padding: 8px 10px;\n"
"font-size: 10pt;\n"
"color: black;"));

        verticalLayout_3->addWidget(regButton);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QDialog *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Demo-Project", nullptr));
        regBox->setTitle(QCoreApplication::translate("Registration", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        backButton->setText(QCoreApplication::translate("Registration", "\342\254\205", nullptr));
        label->setText(QCoreApplication::translate("Registration", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("Registration", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        regButton->setText(QCoreApplication::translate("Registration", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
