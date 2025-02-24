#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../src/fuzzer.h"
#include "test_fuzzer.h"

#define TEST_EXECUTABLE "./mock_extractor.sh"
#define RESULT_DIR "result/"

int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

void create_mock_extractor() {
    FILE *mock = fopen(TEST_EXECUTABLE, "w");
    if (!mock) {
        perror("Error during mock creation");
        exit(EXIT_FAILURE);
    }
    fprintf(mock, "#!/bin/bash\n");
    fprintf(mock, "if [[ $1 == \"test_overflow.tar\" ]]; then\n");
    fprintf(mock, "    echo \"*** The program has crashed ***\"\n");
    fprintf(mock, "    exit 1\n");
    fprintf(mock, "else\n");
    fprintf(mock, "    exit 0\n");
    fprintf(mock, "fi\n");
    fclose(mock);
    chmod(TEST_EXECUTABLE, 0755);
}

void test_fuzzer() {
    printf("=== TEST : Execution of the fuzzer ===\n");

    // Create a fake extractor
    create_mock_extractor();
    printf("Mock extractor created\n");

    // Execute the fuzzer
    execute_fuzzer(TEST_EXECUTABLE);
    printf("Fuzzer executed\n");

    // Verify the results
    char expected_filename[256];
    snprintf(expected_filename, sizeof(expected_filename), "%s/success_test_overflow.tar", RESULT_DIR);

    if (file_exists(expected_filename)) {
        printf("Test succeeded: crash file detected\n");
    } else {
        printf("Test failed: crash file not detected\n");
        exit(EXIT_FAILURE);
    }

    // Clean up
    remove(TEST_EXECUTABLE);
    remove(expected_filename);

    printf("=== END TEST ===\n");
}
