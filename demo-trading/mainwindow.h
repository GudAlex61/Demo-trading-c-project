#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "MakingAPosition.h"
#include <QStandardItemModel>
#include <QWebEngineView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const int userId, double balance, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addTradeButton_clicked();

    void on_uploadButton_clicked();

    void onTradeClicked(const QModelIndex &index);

    void onCryptoSelected(const QString& selectedCrypto);

private:
    Ui::MainWindow *ui;
    double balance;
    int userId;
    std::vector<Position> positions;
    QStandardItemModel* model = nullptr;
    QWebEngineView* webView;
    void loadTradingViewChart(const QString& symbol);
};

#endif // MAINWINDOW_H
