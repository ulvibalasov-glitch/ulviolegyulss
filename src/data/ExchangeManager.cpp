#include "ExchangeManager.h"
#include <iostream>
#include <stdexcept>

double ExchangeManager::getRate(Currency from, Currency to) {
    // Известные пары курсов
    if (from == USD && to == EUR) return Constants::USD_TO_EUR;
    if (from == EUR && to == USD) return Constants::EUR_TO_USD;

    if (from == USD && to == GBP) return Constants::USD_TO_GBP;
    if (from == GBP && to == USD) return Constants::GBP_TO_USD;

    if (from == EUR && to == GBP) return Constants::EUR_TO_GBP;
    if (from == GBP && to == EUR) return Constants::GBP_TO_EUR;

    throw std::runtime_error("Exchange rate not found for selected currency pair");
}

bool ExchangeManager::hasEnoughReserve(Currency currency, double amount) {
    if (currency == USD) return usdReserve >= amount;
    if (currency == EUR) return eurReserve >= amount;
    if (currency == GBP) return gbpReserve >= amount;
    return false;
}

void ExchangeManager::updateReserve(Currency from, Currency to, double amountOut, double amountIn) {
    if (from == USD) usdReserve += amountIn;
    if (from == EUR) eurReserve += amountIn;
    if (from == GBP) gbpReserve += amountIn;

    if (to == USD) usdReserve -= amountOut;
    if (to == EUR) eurReserve -= amountOut;
    if (to == GBP) gbpReserve -= amountOut;
}

void ExchangeManager::checkReserves() {
    if (usdReserve < Constants::CRITICAL_MIN)
        std::cout << "Low reserve for USD: " << usdReserve << "\n";
    if (eurReserve < Constants::CRITICAL_MIN)
        std::cout << "Low reserve for EUR: " << eurReserve << "\n";
    if (gbpReserve < Constants::CRITICAL_MIN)
        std::cout << "Low reserve for GBP: " << gbpReserve << "\n";
}

void ExchangeManager::generateReport(double profit) {
    std::cout << "\n--- Daily Report ---\n";
    std::cout << "USD balance: " << usdReserve << "\n";
    std::cout << "EUR balance: " << eurReserve << "\n";
    std::cout << "GBP balance: " << gbpReserve << "\n";
    std::cout << "Profit earned: " << profit << "\n";
    std::cout << "Cashier bonus (5%): " << profit * Constants::CASHIER_PERCENT << "\n";
    std::cout << "---------------------\n";
}
