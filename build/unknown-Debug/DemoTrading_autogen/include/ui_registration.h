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

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QGroupBox *regBox;
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
        regBox = new QGroupBox(Registration);
        regBox->setObjectName("regBox");
        regBox->setGeometry(QRect(60, 225, 280, 150));
        verticalLayout_3 = new QVBoxLayout(regBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(regBox);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(regBox);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(regBox);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        loginLine = new QLineEdit(regBox);
        loginLine->setObjectName("loginLine");

        verticalLayout_2->addWidget(loginLine);

        passLine = new QLineEdit(regBox);
        passLine->setObjectName("passLine");

        verticalLayout_2->addWidget(passLine);

        secpassLine = new QLineEdit(regBox);
        secpassLine->setObjectName("secpassLine");

        verticalLayout_2->addWidget(secpassLine);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        regButton = new QPushButton(regBox);
        regButton->setObjectName("regButton");

        verticalLayout_3->addWidget(regButton);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QDialog *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Demo-Project", nullptr));
        regBox->setTitle(QCoreApplication::translate("Registration", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
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
