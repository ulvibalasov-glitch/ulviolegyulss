#include "Cashier.h"
#include "ReceiptPrinter.h"
#include <iostream>

Cashier::Cashier(ExchangeManager& mgr) : manager(mgr) {}

void Cashier::exchange(Transaction& tx, bool partial) {
    tx.rate = manager.getRate(tx.from, tx.to);
    double converted = tx.amount * tx.rate;

    if (!manager.hasEnoughReserve(tx.to, converted)) {
        std::cout << "Not enough reserve for " << currencyName(tx.to) << "\n";
        return;
    }

    std::cout << "Exchange approved\n";

    if (partial) {
        double half = converted / 2;
        std::cout << "Partial exchange: " << half << " " << currencyName(tx.to)
                  << " and rest in " << currencyName(tx.from) << "\n";
    } else {
        std::cout << "Client receives: " << converted << " " << currencyName(tx.to) << "\n";
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