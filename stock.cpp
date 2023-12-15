#include "Stock.h"

Stock::Stock(const QString& symbol, double initialPrice) : symbol(symbol), price(initialPrice) {}

const QString& Stock::getSymbol() const {
    return symbol;
}

double Stock::getPrice() const {
    return price;
}

void Stock::updatePrice() {
    // Simulate price fluctuation (for demonstration purposes)
    double percentageChange = (rand() % 100 - 50) / 100.0;  // Random change between -0.5 and 0.5
    price *= (1 + percentageChange);
}
