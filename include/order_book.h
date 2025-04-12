#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <string>

enum class OrderSide {
    BUY,
    SELL
};

struct Order {
    std::string orderId;
    std::string symbol;
    OrderSide side;
    double price;
    int quantity;
    long timestamp;
};

class IOrderBook {
    public:
        virtual ~IOrderBook() = default;

        virtual void addOrder(const Order& order) = 0;

        virtual void matchOrders() = 0;

        virtual void printOrderBook() const = 0;
};

#endif // ORDER_BOOK_H
