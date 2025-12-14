#include "StateRepository.h"
#include <fstream>
#include <sstream>

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
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        file << data[i].usd << " "
             << data[i].eur << " "
             << data[i].gbp << " "
             << data[i].profit << "\n";
    }

    file.close();
    return true;
}

bool StateRepository::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    size = 0; // очищаем репозиторий

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        SystemState state;

        if (!(iss >> state.usd >> state.eur >> state.gbp >> state.profit)) {
            continue; // пропускаем битые строки
        }

        add(state);
    }

    file.close();
    return true;
}

