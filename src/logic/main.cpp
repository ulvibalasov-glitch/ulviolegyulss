#include "ExchangeManager.h"
#include "Transaction.h"
#include "Cashier.h"
#include <ctime>
#include <string>

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

    Transaction tx1 = {USD, EUR, 100, 0.0, getDate()};
    cashier.exchange(tx1);
    cashier.printReceipt(tx1);

    Transaction tx2 = {USD, GBP, 200, 0.0, getDate()};
    cashier.exchange(tx2, true);
    cashier.printReceipt(tx2);

    cashier.generateReport();
    return 0;
}
