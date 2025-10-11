CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 \
           -Isrc -Isrc/logic -Isrc/ui -Isrc/data
SRC = $(wildcard src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = app

.PHONY: all run test clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(BIN)
	./$(BIN)

test: $(BIN) tests/test_basic.sh
	bash tests/test_basic.sh

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(BIN).exe 2>nul || true
	del /Q src\*.o 2>nul || true
else
	rm -f $(BIN) src/**/*.o
endif
