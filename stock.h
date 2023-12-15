#pragma once

#include <QString>

class Stock {
public:
    Stock(const QString& symbol, double initialPrice);
    const QString& getSymbol() const;
    double getPrice() const;
    void updatePrice();

private:
    QString symbol;
    double price;
};
