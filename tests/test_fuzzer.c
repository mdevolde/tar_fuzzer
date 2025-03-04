#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include "../src/fuzzer.h"
#include "test_fuzzer.h"

#define TEST_EXECUTABLE "./mock_extractor.sh"
#define RESULT_DIR "result/"

int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

int is_dir_empty(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return 1;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            return 0;
        }
    }
    closedir(dir);
    return 1;
}

void create_mock_extractor() {
    FILE *mock = fopen(TEST_EXECUTABLE, "w");
    if (!mock) {
        perror("Error during mock creation");
        exit(EXIT_FAILURE);
    }
    fprintf(mock, "#!/bin/bash\n");
    fprintf(mock, "echo \"*** The program has crashed ***\"\n");
    fprintf(mock, "fi\n");
    fclose(mock);
    chmod(TEST_EXECUTABLE, 0755);
}

void test_fuzzer() {
    printf("=== TEST : Execution of the fuzzer ===\n");

    // Check if the result directory exists
    ensure_result_dir();
        
    // Clean up /result directory
    system("rm -f result/*");
    system("rm -rf result");

    // Create a fake extractor
    create_mock_extractor();
    printf("Mock extractor created\n");

    // Execute the fuzzer
    execute_fuzzer(TEST_EXECUTABLE);
    printf("Fuzzer executed\n");

    // If there is files in the result directory, the test is successful
    if (file_exists(RESULT_DIR)) {
        if (!is_dir_empty(RESULT_DIR)) {
            printf("Test succeeded: crash files detected\n");
        } else {
            printf("Test failed: no crash files detected\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Test failed: no crash files detected\n");
        exit(EXIT_FAILURE);
    }

    // Clean up
    remove(TEST_EXECUTABLE);

    // Clean up /result directory
    ensure_result_dir();
    system("rm -f result/*");
    system("rm -rf result");

    printf("=== END TEST ===\n");
}
