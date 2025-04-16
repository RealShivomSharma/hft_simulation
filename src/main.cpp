#include <iostream>
#include <chrono>
#include <thread>
#include "market_data_feed.h"
#include "order_book.h"
#include "trading_strategy.h" // Include the header, not the .cpp

// Factory functions declared elsewhere
IMarketDataFeed* createMarketDataFeed();
IOrderBook* createOrderBook();

int main() {
    // Create the market data feed and order book
    IMarketDataFeed* feed = createMarketDataFeed();
    IOrderBook* orderBook = createOrderBook();

    // Connect the market data feed
    if (!feed->connect()) {
        std::cerr << "Failed to connect to market data feed.\n";
        return 1;
    }

    // Instantiate and start the strategy
    Strategy strategy(feed, orderBook);
    strategy.start();

    // Let the strategy run for 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Stop the strategy and clean up the feed
    strategy.stop();
    feed->disconnect();
    delete feed;
    std::cout << "Market Data feed simulation ended.\n";

    // Manual Order Book Tests
    orderBook->addOrder({"order1", "AAPL", OrderSide::BUY, 150.0, 50, 0});
    orderBook->addOrder({"order2", "AAPL", OrderSide::SELL, 148.0, 20, 0});
    orderBook->addOrder({"order3", "AAPL", OrderSide::BUY, 151.0, 30, 0});

    std::cout << "\nOrder book after adding initial test orders:\n";
    orderBook->printOrderBook();

    orderBook->addOrder({"order4", "AAPL", OrderSide::BUY, 148.0, 20, 0});
    std::cout << "\nOrder book after adding order4:\n";
    orderBook->printOrderBook();

    // Clean up order book
    delete orderBook;
    return 0;
}

