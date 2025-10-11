#pragma once
#include "Transaction.h"
#include <iostream>

std::string currencyName(Currency c);

class ReceiptPrinter {
public:
    void print(const Transaction& tx);
};