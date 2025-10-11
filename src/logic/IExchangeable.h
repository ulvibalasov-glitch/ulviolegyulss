#pragma once
#include "Transaction.h"

class IExchangeable {
public:
    virtual void exchange(Transaction& tx, bool partial = false) = 0;
    virtual void printReceipt(const Transaction& tx) = 0;
};
