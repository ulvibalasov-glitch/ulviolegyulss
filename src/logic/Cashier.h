#pragma once

#include "ExchangeManager.h"
#include "ReceiptPrinter.h"
#include "IExchangeable.h"

class Cashier : public IExchangeable {
private:
    double profit = 0;
    ExchangeManager& manager;
    ReceiptPrinter printer;

public:
    Cashier(ExchangeManager& mgr);
    void exchange(Transaction& tx, bool partial = false) override;
    void printReceipt(const Transaction& tx) override;
    void generateReport();
};