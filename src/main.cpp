#include <iostream>
#include <chrono>
#include <thread>
#include "market_data_feed.h"
#include "order_book.h"

IMarketDataFeed* createMarketDataFeed();
IOrderBook* createOrderBook();
int main() {

    IMarketDataFeed* feed = createMarketDataFeed();

    if (!feed->connect()) {
        std::cerr << "Failed to connect to market data feed." << "\n";
        return 1;
    }

    feed->setDataCallback([](const MarketData& data) {
            std::cout << "Received Tick -> Symbol: " << data.symbol
                << ", Price: " << data.price
                << ", Volume:  " << data.volume
                << ", Timestamp: " << data.timestamp << "\n";
            });
    

    feed->start();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    feed->disconnect();
    delete feed;

    std::cout << "Market Data feed simulation ended." << "\n";

    IOrderBook* orderBook = createOrderBook();

    // Test orders 
    
    orderBook->addOrder({"order1", "AAPL", OrderSide::BUY, 150.0, 50, 0});
    orderBook->addOrder({"order2", "AAPL", OrderSide::SELL, 148.0, 20, 0});
    orderBook->addOrder({"order1", "AAPL", OrderSide::BUY, 151.0, 30, 0});

    orderBook->printOrderBook();

    orderBook->addOrder({"order4", "AAPL", OrderSide::BUY, 148.0, 20, 0});
    orderBook->printOrderBook();

    delete orderBook;
    return 0;

}
