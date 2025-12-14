#include "StateRepository.h"
#include <fstream>

StateRepository::StateRepository() {
    capacity = 4;
    size = 0;
    data = new SystemState[capacity];
}

StateRepository::~StateRepository() {
    delete[] data;
}

void StateRepository::grow() {
    capacity *= 2;
    SystemState* newData = new SystemState[capacity];

    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}

void StateRepository::add(const SystemState& item) {
    if (size >= capacity) {
        grow();
    }
    data[size++] = item;
}

int StateRepository::count() const {
    return size;
}

const SystemState& StateRepository::get(int index) const {
    return data[index];
}

bool StateRepository::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    out << size << "\n";
    for (int i = 0; i < size; ++i) {
        out << data[i].usd << " "
            << data[i].eur << " "
            << data[i].gbp << " "
            << data[i].profit << "\n";
    }

    out.close();
    return true;
}

bool StateRepository::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    int countFromFile;
    in >> countFromFile;

    size = 0;
    for (int i = 0; i < countFromFile; ++i) {
        SystemState s;
        in >> s.usd >> s.eur >> s.gbp >> s.profit;
        add(s);
    }

    in.close();
    return true;
}
