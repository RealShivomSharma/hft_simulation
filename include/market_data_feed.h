#ifndef MARKET_DATA_FEED_H
#define MARKET_DATA_FEED_H

#include <string>
#include <functional>

// Create a structure to capture tickers


struct MarketData {
    std::string symbol; // E.g. AAPL
    double price; // Current Price
    int volume;  // Volume of ticker
    long timestamp; //timestamp in milliseconds
};

// Market Intertface 
class IMarketDataFeed {
    public:
        virtual ~IMarketDataFeed() = default;

        // Connect to data sourdce 
        
        virtual bool connect() = 0;

        // Disconnect from data source
        virtual bool disconnect() = 0;

        // Callback for when new data arrives

        virtual void setDataCallback(std::function<void(const MarketData&)> callback) = 0;

        // Start data feed 

        virtual void start() = 0;
};

#endif // MARKET_DATA_FEED_H
