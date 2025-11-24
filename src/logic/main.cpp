#include "ExchangeManager.h"
#include "Transaction.h"
#include "Cashier.h"
#include <ctime>
#include <string>
#include <iostream>
#include <stdexcept>

static std::string getDate() {
    time_t now = time(nullptr);
    char* dt = ctime(&now);
    std::string date(dt);
    if (!date.empty() && date.back() == '\n') {
        date.pop_back();
    }
    return date;
}

int main() {
    ExchangeManager manager;
    Cashier cashier(manager);

    Transaction tx1 = { USD, EUR, 100, 0.0, getDate() };

    try {
        cashier.exchange(tx1);
        cashier.printReceipt(tx1);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Input error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Operation failed: " << e.what() << std::endl;
    }

    Transaction tx2 = { USD, GBP, 200, 0.0, getDate() };

    try {
        cashier.exchange(tx2, true);
        cashier.printReceipt(tx2);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Input error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Operation failed: " << e.what() << std::endl;
    }

    cashier.generateReport();

    return 0;
}
