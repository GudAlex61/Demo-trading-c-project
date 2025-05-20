/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *longRadio;
    QSpacerItem *horizontalSpacer;
    QRadioButton *shortRadio;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *amountSpinBox;
    QPushButton *addTradeButton;
    QPushButton *uploadButton;
    QTableView *tradesView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(691, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(200, 80, 211, 191));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        longRadio = new QRadioButton(groupBox);
        longRadio->setObjectName("longRadio");

        horizontalLayout->addWidget(longRadio);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        shortRadio = new QRadioButton(groupBox);
        shortRadio->setObjectName("shortRadio");

        horizontalLayout->addWidget(shortRadio);


        verticalLayout->addLayout(horizontalLayout);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(1);
        spinBox->setMaximum(100);

        horizontalLayout_3->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        amountSpinBox = new QDoubleSpinBox(groupBox);
        amountSpinBox->setObjectName("amountSpinBox");
        amountSpinBox->setEnabled(true);
        amountSpinBox->setMaximum(999999.989999999990687);

        horizontalLayout_2->addWidget(amountSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        addTradeButton = new QPushButton(groupBox);
        addTradeButton->setObjectName("addTradeButton");

        verticalLayout->addWidget(addTradeButton);

        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName("uploadButton");
        uploadButton->setGeometry(QRect(370, 282, 81, 20));
        tradesView = new QTableView(centralwidget);
        tradesView->setObjectName("tradesView");
        tradesView->setGeometry(QRect(170, 300, 281, 161));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 691, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Demo-Trading", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "C\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\203\321\216 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        longRadio->setText(QCoreApplication::translate("MainWindow", "Long", nullptr));
        shortRadio->setText(QCoreApplication::translate("MainWindow", "Short", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "BTC", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "ETH", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "SOL", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "XRP", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "PEPE", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\265\321\207\320\276", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "C\321\203\320\274\320\274\320\260", nullptr));
        addTradeButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\202\321\200\320\265\320\271\320\264", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
