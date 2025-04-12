#include "order_book.h"
#include <map>
#include <list>
#include <iostream>


class SimpleOrderBook : public IOrderBook {
    public:
        SimpleOrderBook() = default;
        ~SimpleOrderBook() override = default;

        void addOrder(const Order& order) override {
            if (order.side == OrderSide::BUY) {
                bids[order.price].push_back(order);
            }
            else {
                asks[order.price].push_back(order);
            }

            matchOrders();
        }

        void matchOrders() override {

            while (!bids.empty() && !asks.empty()) {

                auto highestBid = --bids.end(); // last element of bids (largest price)
                auto lowestAsk = asks.begin(); // lowest price first order

                if (highestBid->first >= lowestAsk->first) {
                    auto& bidList = highestBid->second;
                    auto& askList = lowestAsk->second;

                    Order& bidOrder  = bidList.front();
                    Order& askOrder  = askList.front();

                    int executedQuantity = std::min(bidOrder.quantity, askOrder.quantity);
                    double executionPrice = (bidOrder.price + askOrder.price) / 2.0;

                    std::cout << "Trade executed: "
                        << executedQuantity << " @ " << executionPrice
                        << " between " << bidOrder.orderId << " (BUY) and " 
                        << askOrder.orderId << " (SELL)" << "\n";
                    
                    bidOrder.quantity -= executedQuantity;
                    askOrder.quantity -= executedQuantity;

                    if (bidOrder.quantity == 0) {
                        bidList.pop_front();
                    }

                    if (askOrder.quantity == 0) {
                        askList.pop_front();
                    }

                    if (bidList.empty()) {
                        bids.erase(highestBid->first);
                    }
                    if (askList.empty()) {
                        asks.erase(lowestAsk->first);
                    }

                }
                else {
                    // NO matches
                    break;
                }

            }
        }

        void printOrderBook() const override {
            std::cout << "--- Order Book ---" << "\n";

            std::cout << "Bids:" << "\n";

            for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
                for (const auto& order : it->second) {
                    std::cout << " Price: " << it->first
                        << ", Qty: " << order.quantity
                        << ", ID: " << order.orderId << "\n";
                }
            }

            std::cout << "Asks:" << "\n";

            for (auto it = asks.begin(); it != asks.end(); ++it) {
                for (const auto& order : it->second) {
                    std::cout << " Price: " << it->first
                        << ", Qty: " << order.quantity
                        << ", ID: " << order.orderId << "\n";
                }
            }

            std::cout << "------------------------" << "\n";
        }
    private:

        std::map<double, std::list<Order>> bids;
        std::map<double, std::list<Order>> asks;
};

IOrderBook* createOrderBook() {
    return new SimpleOrderBook();
}

