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
#include <QtWebEngineWidgets/QWebEngineView>
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
    QRadioButton *shortRadio;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *amountSpinBox;
    QPushButton *addTradeButton;
    QWebEngineView *webView;
    QPushButton *uploadButton;
    QTableView *tradesView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(852, 988);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: white; color: black;"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 20, 740, 360));
        groupBox->setStyleSheet(QString::fromUtf8("\n"
"            QGroupBox {\n"
"              border: 1px solid #E0E0E0;\n"
"              border-radius: 8px;\n"
"              margin-top: 20px;\n"
"              padding-top: 25px;\n"
"              font: bold 14pt \"Segoe UI\";\n"
"              color: black;\n"
"              background: white;\n"
"            }\n"
"            QGroupBox::title {\n"
"              subcontrol-origin: margin;\n"
"              left: 15px;\n"
"            }\n"
"          "));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        longRadio = new QRadioButton(groupBox);
        longRadio->setObjectName("longRadio");
        longRadio->setStyleSheet(QString::fromUtf8("\n"
"                      QRadioButton {\n"
"                        background: #F5F5F5;\n"
"                        border: 1px solid #E0E0E0;\n"
"                        border-radius: 8px;\n"
"                        padding: 12px 24px;\n"
"                        min-width: 140px;\n"
"                        min-height: 40px;\n"
"                        font: bold 12pt \"Segoe UI\";\n"
"                        color: black;\n"
"                      }\n"
"                      QRadioButton:checked { \n"
"                        background: #4CAF50; \n"
"                        color: white; \n"
"                      }\n"
"                    "));

        horizontalLayout->addWidget(longRadio);

        shortRadio = new QRadioButton(groupBox);
        shortRadio->setObjectName("shortRadio");
        shortRadio->setStyleSheet(QString::fromUtf8("\n"
"                      QRadioButton {\n"
"                        background: #F5F5F5;\n"
"                        border: 1px solid #E0E0E0;\n"
"                        border-radius: 8px;\n"
"                        padding: 12px 24px;\n"
"                        min-width: 140px;\n"
"                        min-height: 40px;\n"
"                        font: bold 12pt \"Segoe UI\";\n"
"                        color: black;\n"
"                      }\n"
"                      QRadioButton:checked { \n"
"                        background: #F44336; \n"
"                        color: white;\n"
"                      }\n"
"                    "));

        horizontalLayout->addWidget(shortRadio);


        verticalLayout->addLayout(horizontalLayout);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setStyleSheet(QString::fromUtf8("\n"
"                  QComboBox {\n"
"                    border: 1px solid #E0E0E0;\n"
"                    border-radius: 6px;\n"
"                    padding: 10px;\n"
"                    font: 12pt \"Segoe UI\";\n"
"                    min-width: 200px;\n"
"                    color: black;\n"
"                  }\n"
"                "));

        verticalLayout->addWidget(comboBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\"; color: black;"));

        horizontalLayout_3->addWidget(label);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setStyleSheet(QString::fromUtf8("\n"
"                      QSpinBox {\n"
"                        border: 1px solid #E0E0E0;\n"
"                        border-radius: 6px;\n"
"                        padding: 10px;\n"
"                        min-width: 120px;\n"
"                        font: 12pt \"Segoe UI\";\n"
"                        color: black;\n"
"                      }\n"
"                      QSpinBox::up-button, QSpinBox::down-button { \n"
"                        width: 24px; \n"
"                      }\n"
"                    "));
        spinBox->setMinimum(1);
        spinBox->setMaximum(100);

        horizontalLayout_3->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\"; color: black;"));

        horizontalLayout_2->addWidget(label_2);

        amountSpinBox = new QDoubleSpinBox(groupBox);
        amountSpinBox->setObjectName("amountSpinBox");
        amountSpinBox->setEnabled(true);
        amountSpinBox->setStyleSheet(QString::fromUtf8("\n"
"                      QDoubleSpinBox {\n"
"                        border: 1px solid #E0E0E0;\n"
"                        border-radius: 6px;\n"
"                        padding: 10px;\n"
"                        min-width: 200px;\n"
"                        font: 12pt \"Segoe UI\";\n"
"                        color: black;\n"
"                      }\n"
"                    "));
        amountSpinBox->setMaximum(999999.989999999990687);

        horizontalLayout_2->addWidget(amountSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        addTradeButton = new QPushButton(groupBox);
        addTradeButton->setObjectName("addTradeButton");
        addTradeButton->setEnabled(false);
        addTradeButton->setStyleSheet(QString::fromUtf8("\n"
"                  QPushButton {\n"
"                    color: white;\n"
"                    padding: 16px 32px;\n"
"                    border-radius: 8px;\n"
"                    font: bold 14pt \"Segoe UI\";\n"
"                    min-width: 240px;\n"
"                    background: #9E9E9E;\n"
"                    border: none;\n"
"                  }\n"
"                  QPushButton:enabled {\n"
"                    background: #4CAF50;\n"
"                  }\n"
"                  QPushButton:hover:enabled {\n"
"                    background: #45A049;\n"
"                  }\n"
"                "));

        verticalLayout->addWidget(addTradeButton);

        webView = new QWebEngineView(centralwidget);
        webView->setObjectName("webView");
        webView->setGeometry(QRect(30, 390, 740, 240));
        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName("uploadButton");
        uploadButton->setGeometry(QRect(710, 640, 41, 31));
        uploadButton->setStyleSheet(QString::fromUtf8("\n"
"            QPushButton {\n"
"              background: #E0E0E0;\n"
"              color: #616161;\n"
"              border-radius: 6px;\n"
"              font: bold 12pt \"Segoe UI\";\n"
"            }\n"
"            QPushButton:hover {\n"
"              background: #BDBDBD;\n"
"            }\n"
"          "));
        tradesView = new QTableView(centralwidget);
        tradesView->setObjectName("tradesView");
        tradesView->setGeometry(QRect(30, 670, 600, 250));
        tradesView->setStyleSheet(QString::fromUtf8("\n"
"            QTableView {\n"
"              border: none;\n"
"              gridline-color: transparent;\n"
"              alternate-background-color: #FAFAFA;\n"
"              font: 12pt \"Segoe UI\";\n"
"              color: black;\n"
"            }\n"
"            QHeaderView::section {\n"
"              background: white;\n"
"              border: none;\n"
"              border-bottom: 2px solid #E0E0E0;\n"
"              padding: 12px;\n"
"              font: bold 12pt \"Segoe UI\";\n"
"              color: black;\n"
"            }\n"
"            QTableView::item {\n"
"              border-bottom: 1px solid #E0E0E0;\n"
"              padding: 10px;\n"
"              color: black;\n"
"              height: 20px;\n"
"            }\n"
"          "));
        tradesView->setSelectionMode(QAbstractItemView::SingleSelection);
        tradesView->setSelectionBehavior(QAbstractItemView::SelectItems);
        tradesView->setShowGrid(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 852, 23));
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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\203\321\216 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        longRadio->setText(QCoreApplication::translate("MainWindow", "LONG", nullptr));
        shortRadio->setText(QCoreApplication::translate("MainWindow", "SHORT", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "BTC", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "ETH", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "SOL", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "XRP", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "PEPE", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\265\321\207\320\276", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\260", nullptr));
        addTradeButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\236\320\227\320\224\320\220\320\242\320\254 \320\237\320\236\320\227\320\230\320\246\320\230\320\256", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainWindow", "\342\237\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
