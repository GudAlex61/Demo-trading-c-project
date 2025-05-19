#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "MakingAPosition.h"

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

private:
    Ui::MainWindow *ui;
    double balance;
    int userId;
    std::vector<Position> positions;
};

#endif // MAINWINDOW_H
