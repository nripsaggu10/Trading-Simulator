#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    simulator = new TradingSimulator(this);

    // Connect signals and slots
    connect(simulator, &TradingSimulator::stockPricesUpdated, this, &MainWindow::updateStockTable);

    // Setup stock table
    ui->stockTable->setColumnCount(2);
    ui->stockTable->setHorizontalHeaderLabels({"Symbol", "Price"});

    // Display stocks in the table
    updateStockTable();

    // Display portfolio value
    updatePortfolioLabel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateStockTable() {
    const auto& stocks = simulator->getStocks();
    ui->stockTable->setRowCount(stocks.size());

    for (int row = 0; row < stocks.size(); ++row) {
        QTableWidgetItem* symbolItem = new QTableWidgetItem(stocks[row].getSymbol());
        QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(stocks[row].getPrice()));

        ui->stockTable->setItem(row, 0, symbolItem);
        ui->stockTable->setItem(row, 1, priceItem);
    }
}

void MainWindow::updatePortfolioLabel() {
    const auto& portfolio = simulator->getPortfolio();
    ui->portfolioLabel->setText("Portfolio Value: $" + QString::number(portfolio.calculatePortfolioValue()));
}
