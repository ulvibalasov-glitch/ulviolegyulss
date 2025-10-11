#pragma once
#include "Transaction.h"
#include "Constants.h"

class ExchangeManager {
private:
    double usdReserve = 1000;
    double eurReserve = 800;
    double gbpReserve = 500;

public:
    double getRate(Currency from, Currency to);
    bool hasEnoughReserve(Currency currency, double amount);
    void updateReserve(Currency from, Currency to, double amountOut, double amountIn);
    void checkReserves();
    void generateReport(double profit);
};