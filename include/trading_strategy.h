#ifndef TRADING_STRATEGY_H
#define TRADING_STRATEGY_H

#include "market_data_feed.h"
#include "order_book.h"
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>

inline std::string generateOrderId(int counter) {
    std::ostringstream oss;
    oss << "order_" << counter;
    return oss.str();
}

class Strategy {
    public: 
        Strategy(IMarketDataFeed* feed, IOrderBook* book);
        void start();
        void stop();
    private:
        IMarketDataFeed* dataFeed;
        IOrderBook* orderBook;
        int orderCounter;

        const double buyThres = 130.0;
        const double sellThres = 160.0;
        
        void processTick(const MarketData& tick);

};

#endif // TRADING_STRATEGY_H
