CC = gcc
CFLAGS = -Wall -Wextra -std=c17
OBJ = src/main.o src/tar_header.o src/tar_archive.o
TEST_OBJ = tests/test_main.o tests/test_tar_header.o src/tar_header.o tests/test_tar_archive.o src/tar_archive.o
DEPS = include/tar_header.h include/tar_archive.h
EXEC = fuzzer
TEST_EXEC = test_main

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
	rm -f src/*.o tests/*.o $(EXEC) $(TEST_EXEC) test_main test_header.bin

.PHONY: all clean test
