#pragma once
#include <string>

enum Currency { USD, EUR, GBP };

struct Transaction {
    Currency from;
    Currency to;
    double amount;
    double rate;
    std::string date;
};

