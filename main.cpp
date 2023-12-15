#include <iostream>
#include <vector>
#include <algorithm>
#include <QCoreApplication>
#include <QDateTime>
#include <QTimer>

class Stock {
public:
    Stock(const QString& symbol, double initialPrice) : symbol(symbol), price(initialPrice) {}

    const QString& getSymbol() const {
        return symbol;
    }

    double getPrice() const {
        return price;
    }

    void updatePrice() {
        // Simulate price fluctuation (for demonstration purposes)
        double percentageChange = (rand() % 100 - 50) / 100.0;  // Random change between -0.5 and 0.5
        price *= (1 + percentageChange);
    }

private:
    QString symbol;
    double price;
};

class Portfolio {
public:
    void buyStock(const Stock& stock, int quantity) {
        stocks.push_back({stock, quantity});
    }

    void sellStock(const Stock& stock, int quantity) {
        auto it = std::find_if(stocks.begin(), stocks.end(), [&stock](const auto& item) {
            return item.stock.getSymbol() == stock.getSymbol();
        });

        if (it != stocks.end() && it->quantity >= quantity) {
            it->quantity -= quantity;
            if (it->quantity == 0) {
                stocks.erase(it);
            }
        } else {
            std::cout << "Error: Not enough stocks to sell." << std::endl;
        }
    }

    double calculatePortfolioValue() const {
        double value = 0.0;
        for (const auto& item : stocks) {
            value += item.stock.getPrice() * item.quantity;
        }
        return value;
    }

    const std::vector<PortfolioItem>& getStocks() const {
        return stocks;
    }

private:
    struct PortfolioItem {
        Stock stock;
        int quantity;
    };

    std::vector<PortfolioItem> stocks;
};

class TradingSimulator : public QObject {
    Q_OBJECT
public:
    TradingSimulator(QObject* parent = nullptr) : QObject(parent) {
        stocks.emplace_back("AAPL", 150.0);
        stocks.emplace_back("GOOGL", 2500.0);

        // Connect a timer to update stock prices every second
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &TradingSimulator::updateStockPrices);
        timer->start(1000);
    }

    void simulateTrading() {
        // Simulate buying and selling
        portfolio.buyStock(stocks[0], 10);
        portfolio.buyStock(stocks[1], 5);

        portfolio.sellStock(stocks[0], 3);
        portfolio.sellStock(stocks[1], 2);

        // Display portfolio value
        std::cout << "Portfolio Value: $" << portfolio.calculatePortfolioValue() << std::endl;
    }

    const std::vector<Stock>& getStocks() const {
        return stocks;
    }

    const Portfolio& getPortfolio() const {
        return portfolio;
    }

signals:
    void stockPricesUpdated();

private slots:
    void updateStockPrices() {
        for (auto& stock : stocks) {
            stock.updatePrice();
        }

        emit stockPricesUpdated();
    }

private:
    std::vector<Stock> stocks;
    Portfolio portfolio;
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    TradingSimulator simulator;
    simulator.simulateTrading();

    return a.exec();
}
