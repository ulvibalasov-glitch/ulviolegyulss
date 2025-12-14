#pragma once
#include "SystemState.h"
#include <string>

class StateRepository {
private:
    SystemState* data;
    int size;
    int capacity;

    void grow();

public:
    StateRepository();
    ~StateRepository();

    void add(const SystemState& item);
    int count() const;
    const SystemState& get(int index) const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
};
