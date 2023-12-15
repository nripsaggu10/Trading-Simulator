#include "TradingSimulator.h"
#include <QTimer>

TradingSimulator::TradingSimulator(QObject* parent) : QObject(parent) {
    stocks.emplace_back("AAPL", 150.0);
    stocks.emplace_back("GOOGL", 2500.0);

    // Connect a timer to update stock prices every second
    QTimer* timer = new QTimer
