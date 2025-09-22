#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// --- Currency Enum ---
enum Currency { USD, EUR, GBP };

string currencyName(Currency c) {
    if (c == USD) return "USD";
    if (c == EUR) return "EUR";
    if (c == GBP) return "GBP";
    return "Unknown";
}

// --- Get current date as string ---
string getDate() {
    time_t now = time(0);
    return string(ctime(&now)); // Includes newline at the end
}

// --- Transaction Struct ---
struct Transaction {
    Currency from;
    Currency to;
    double amount;
    double rate;
    string date;
};

// --- Receipt Class ---
class Receipt {
public:
    void print(const Transaction& tx) {
        cout << "\n--- Receipt ---\n";
        cout << "Date: " << tx.date;
        cout << "Exchanged: " << tx.amount << " " << currencyName(tx.from)
             << " to " << currencyName(tx.to) << "\n";
        cout << "Rate: " << tx.rate << "\n";
        cout << "----------------\n";
    }
};

// --- ExchangeManager Class ---
class ExchangeManager {
private:
    double usdReserve = 1000;
    double eurReserve = 800;
    double gbpReserve = 500;
    double criticalMin = 100;

public:
    double getRate(Currency from, Currency to) {
        if (from == USD && to == EUR) return 0.85;
        if (from == EUR && to == USD) return 1.18;
        if (from == USD && to == GBP) return 0.75;
        if (from == GBP && to == USD) return 1.33;
        if (from == EUR && to == GBP) return 0.88;
        if (from == GBP && to == EUR) return 1.14;
        return 1.0;
    }

    bool hasEnoughReserve(Currency currency, double amount) {
        if (currency == USD) return usdReserve >= amount;
        if (currency == EUR) return eurReserve >= amount;
        if (currency == GBP) return gbpReserve >= amount;
        return false;
    }

    void updateReserve(Currency from, Currency to, double amountOut, double amountIn) {
        if (from == USD) usdReserve += amountIn;
        if (from == EUR) eurReserve += amountIn;
        if (from == GBP) gbpReserve += amountIn;

        if (to == USD) usdReserve -= amountOut;
        if (to == EUR) eurReserve -= amountOut;
        if (to == GBP) gbpReserve -= amountOut;
    }

    void checkReserves() {
        if (usdReserve < criticalMin)
            cout << "Low reserve for USD: " << usdReserve << "\n";
        if (eurReserve < criticalMin)
            cout << "Low reserve for EUR: " << eurReserve << "\n";
        if (gbpReserve < criticalMin)
            cout << "Low reserve for GBP: " << gbpReserve << "\n";
    }

    void generateReport(double profit) {
        cout << "\n--- Daily Report ---\n";
        cout << "USD balance: " << usdReserve << "\n";
        cout << "EUR balance: " << eurReserve << "\n";
        cout << "GBP balance: " << gbpReserve << "\n";
        cout << "Profit earned: " << profit << "\n";
        cout << "Cashier bonus (5%): " << profit * 0.05 << "\n";
        cout << "---------------------\n";
    }
};

// --- Cashier Class ---
class Cashier {
private:
    double profit = 0;
    ExchangeManager& manager;

public:
    Cashier(ExchangeManager& mgr) : manager(mgr) {}

    void exchange(Transaction& tx, bool partial = false) {
        tx.rate = manager.getRate(tx.from, tx.to);
        double converted = tx.amount * tx.rate;

        if (!manager.hasEnoughReserve(tx.to, converted)) {
            cout << "Not enough reserve for " << currencyName(tx.to) << "\n";
            return;
        }

        cout << "Exchange approved\n";

        if (partial) {
            double half = converted / 2;
            cout << "Partial exchange: " << half << " " << currencyName(tx.to)
                 << " and rest in " << currencyName(tx.from) << "\n";
        } else {
            cout << "Client receives: " << converted << " " << currencyName(tx.to) << "\n";
        }

        profit += converted * 0.05;
        manager.updateReserve(tx.from, tx.to, converted, tx.amount);
        manager.checkReserves();
    }

    void printReceipt(const Transaction& tx) {
        Receipt r;
        r.print(tx);
    }

    void generateReport() {
        manager.generateReport(profit);
    }
};

// --- Main Function ---
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
