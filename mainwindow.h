#pragma once

#include <QMainWindow>
#include <QTableWidget>

#include "TradingSimulator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void updateStockTable();
    void updatePortfolioLabel();

private:
    Ui::MainWindow* ui;
    TradingSimulator* simulator;
};
