#include <trading_strategy.h>

Strategy::Strategy(IMarketDataFeed* feed, IOrderBook* book):
    dataFeed(feed), orderBook(book), orderCounter(0) {}
        

void Strategy::start() {
    dataFeed->setDataCallback([this](const MarketData& tick) {
            this->processTick(tick);
            });
}

void Strategy::stop() {
    // dataFeed->disconnect();
}

void Strategy::processTick(const MarketData& tick) {

    if (tick.price < buyThres) {
        Order newOrder;
        newOrder.orderId = generateOrderId(++orderCounter);
        newOrder.symbol = tick.symbol;
        newOrder.side = OrderSide::BUY;
        newOrder.price = tick.price;
        newOrder.quantity = 10;
        newOrder.timestamp = tick.timestamp;
        std::cout << "Placing BUY order: " << newOrder.orderId << "@ " << newOrder.price << "\n";
        orderBook->addOrder(newOrder);
    }

    else if (tick.price > sellThres) {
        Order newOrder;
        newOrder.orderId = generateOrderId(++orderCounter);
        newOrder.symbol = tick.symbol;
        newOrder.side = OrderSide::SELL;
        newOrder.price = tick.price;
        newOrder.quantity = 10;
        newOrder.timestamp = tick.timestamp;
        std::cout << "Placing SELL order: " << newOrder.orderId << "@ " << newOrder.price << "\n";
        orderBook->addOrder(newOrder);
    }
    orderBook->printOrderBook();
}


