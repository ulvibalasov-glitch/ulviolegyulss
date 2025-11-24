#include "Cashier.h"
#include "ReceiptPrinter.h"
#include <iostream>
#include <stdexcept>

Cashier::Cashier(ExchangeManager& mgr) : manager(mgr) {}

void Cashier::exchange(Transaction& tx, bool partial) {
    if (tx.amount <= 0.0) {
        throw std::invalid_argument("Amount must be positive");
    }

    if (tx.from == tx.to) {
        throw std::invalid_argument("Source and target currencies must be different");
    }

    tx.rate = manager.getRate(tx.from, tx.to);

    double converted = tx.amount * tx.rate;

    if (!manager.hasEnoughReserve(tx.to, converted)) {
        throw std::runtime_error("Not enough reserve for target currency");
    }

    std::cout << "Exchange approved\n";

    if (partial) {
        double half = converted / 2.0;
        std::cout << "Partial exchange: " << half << " " << currencyName(tx.to)
                  << " and rest in " << currencyName(tx.from) << "\n";
    } else {
        std::cout << "Client receives: " << converted << " "
                  << currencyName(tx.to) << "\n";
    }

    profit += converted * Constants::CASHIER_PERCENT;
    manager.updateReserve(tx.from, tx.to, converted, tx.amount);
    manager.checkReserves();
}

void Cashier::printReceipt(const Transaction& tx) {
    printer.print(tx);
}

void Cashier::generateReport() {
    manager.generateReport(profit);
}
