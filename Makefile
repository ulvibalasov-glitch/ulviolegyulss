CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
BIN=app

.PHONY: all run test clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

run: $(BIN)
	./$(BIN)

test: $(BIN) tests/test_basic.sh
	bash tests/test_basic.sh

clean:
	rm -f $(BIN) src/*.o
