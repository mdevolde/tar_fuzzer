CC = gcc
CFLAGS = -Wall -Wextra -std=c17
OBJ = src/main.o src/tar_header.o
TEST_OBJ = tests/test_tar_header.o src/tar_header.o
DEPS = include/tar_header.h
EXEC = fuzzer
TEST_EXEC = test_tar_header

all: $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST_EXEC): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f src/*.o tests/*.o $(EXEC) $(TEST_EXEC)

.PHONY: all clean test
