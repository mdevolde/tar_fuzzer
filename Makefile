CC = gcc
LD = gcc
CFLAGS = -Wall -Wextra -std=c17 -Isrc -ggdb -O0
LDFLAGS = -ggdb
MAIN = src/main.o
OBJ_W_MAIN = src/tar_header.o src/tar_archive.o
OBJ = $(MAIN) $(OBJ_W_MAIN)
TEST_OBJ = tests/test_main.o tests/test_tar_header.o tests/test_tar_archive.o tests/test_tar_archive_longfile.o $(OBJ_W_MAIN)
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

