# Compiler and options
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Isrc -ggdb -O0 -MMD -MP
LDFLAGS = -ggdb

# Names of executables and object files
FUZZER = fuzzer
FUZZERTEST = fuzzer_test

SRC_DIR = src
TESTS_DIR = tests

# Sources and objects for the main fuzzer, excluding main.c
FUZZER_SOURCES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/attacks/*.c))
FUZZER_OBJECTS = $(FUZZER_SOURCES:.c=.o)
FUZZER_DEPFILES = $(FUZZER_OBJECTS:.o=.d)

# Sources and objects for the main.c file of the fuzzer
FUZZER_MAIN_SOURCES = $(SRC_DIR)/main.c
FUZZER_MAIN_OBJECTS = $(FUZZER_MAIN_SOURCES:.c=.o)
FUZZER_MAIN_DEPFILES = $(FUZZER_MAIN_OBJECTS:.o=.d)

# Sources and objects for the test executable
FUZZERTEST_SOURCES = $(wildcard $(TESTS_DIR)/*.c)
FUZZERTEST_OBJECTS = $(FUZZERTEST_SOURCES:.c=.o)
FUZZERTEST_DEPFILES = $(FUZZERTEST_OBJECTS:.o=.d)

# Special targets that don't produce files
.PHONY: all clean test

# Main compilation targets
all: $(FUZZER) $(FUZZERTEST)

# Rule for building the fuzzer executable
$(FUZZER): $(FUZZER_OBJECTS) $(FUZZER_MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Rule for building the fuzzer test executable
$(FUZZERTEST): $(FUZZERTEST_OBJECTS) $(FUZZER_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Automatically include dependency files generated by the compiler
-include $(FUZZER_DEPFILES)
-include $(FUZZERTEST_DEPFILES)

# Rule to run tests using the fuzzer_test executable
test: $(FUZZERTEST)
	./$(FUZZERTEST)

# Clean up generated files
clean:
	rm -f $(FUZZER) $(FUZZERTEST) $(FUZZER_OBJECTS) $(FUZZER_DEPFILES) $(FUZZER_MAIN_OBJECTS) $(FUZZER_MAIN_DEPFILES) $(FUZZERTEST_OBJECTS) $(FUZZERTEST_DEPFILES) *.tar *.txt
