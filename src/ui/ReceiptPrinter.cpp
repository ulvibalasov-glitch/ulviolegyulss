#include "ReceiptPrinter.h"

std::string currencyName(Currency c) {
    switch (c) {
        case USD: return "USD";
        case EUR: return "EUR";
        case GBP: return "GBP";
        default: return "Unknown";
    }
}

void ReceiptPrinter::print(const Transaction& tx) {
    std::cout << "\n--- Receipt ---\n";
    std::cout << "Date: " << tx.date;
    std::cout << "Exchanged: " << tx.amount << " " << currencyName(tx.from)
              << " to " << currencyName(tx.to) << "\n";
    std::cout << "Rate: " << tx.rate << "\n";
    std::cout << "----------------\n";
}