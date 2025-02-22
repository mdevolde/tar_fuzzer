CC = gcc
CFLAGS = -Wall -Wextra -std=c17
OBJ = src/main.o src/tar_header.o
DEPS = include/tar_header.h
EXEC = fuzzer

all: $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o $(EXEC)

.PHONY: all clean
