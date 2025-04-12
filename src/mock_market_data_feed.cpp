#include "market_data_feed.h"
#include <thread>
#include <chrono>
#include <random>
#include <iostream>

class MockMarketDataFeed: public IMarketDataFeed {

    public: 
        MockMarketDataFeed() : running(false) {}

        bool connect() override {
            std::cout << "MockMarketDataFeed connected." << "\n";
            return true;
        }

        bool disconnect() override {
            std::cout << "MockMarketDataFeed disconnected." << "\n";
            running = false;
            if (dataThread.joinable())
                dataThread.join();
            return true;
        }

       void setDataCallback(std::function<void(const MarketData&)> callback) override {
           dataCallback = callback;
       }

        void start() override {
            running = true;
            dataThread = std::thread(&MockMarketDataFeed::simulateData, this);
        }

        ~MockMarketDataFeed() override {
            disconnect();
        }
    private:

        std::atomic<bool> running;
        std::thread dataThread;
        std::function<void(const MarketData&)> dataCallback;

        //Simulate incoming market data
        void simulateData() {
            std::default_random_engine generator;
            std::uniform_real_distribution<double> priceDist(100.0, 200.0);
            std::uniform_int_distribution<int> volumeDist(1,1000);

            while(running) {
                MarketData data;
                data.symbol = "AAPL";
                data.price = priceDist(generator);
                data.volume = volumeDist(generator);
                data.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()).count();

                if (dataCallback) {
                    dataCallback(data);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            }
        }
};

IMarketDataFeed* createMarketDataFeed() {
    return new MockMarketDataFeed();
}

void destroyMarketDataFeed(IMarketDataFeed* feed) {
    delete feed;
}


