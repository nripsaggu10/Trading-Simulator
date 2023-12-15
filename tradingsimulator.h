#pragma once

#include <QObject>
#include <vector>
#include "Stock.h"
#include "Portfolio.h"

class TradingSimulator : public QObject {
    Q_OBJECT

public:
    TradingSimulator(QObject* parent = nullptr);
    void simulateTrading();

    const std::vector<Stock>& getStocks() const;
    const Portfolio& getPortfolio() const;

signals:
    void stockPricesUpdated();

private slots:
    void updateStockPrices();

private:
    std::vector<Stock> stocks;
    Portfolio portfolio;
};
