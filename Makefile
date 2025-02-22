CC = gcc
LD = gcc
CFLAGS = -Wall -Wextra -std=c17 -Isrc -ggdb -O0
LDFLAGS = -ggdb
OBJ = src/main.o src/tar_header.o src/tar_archive.o
TEST_OBJ = tests/test_main.o tests/test_tar_header.o src/tar_header.o tests/test_tar_archive.o src/tar_archive.o
EXEC = fuzzer
TEST_EXEC = test_main

.PHONY: all clean test


all: $(EXEC)


$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(TEST_EXEC): $(TEST_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f src/*.o tests/*.o $(EXEC) $(TEST_EXEC) test_main test_header.bin

