#include <iostream>
#include <chrono>
#include <thread>
#include "market_data_feed.h"

IMarketDataFeed* createMarketDataFeed();
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

    return 0;

}
