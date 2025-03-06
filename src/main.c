#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fuzzer.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_executable>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char path[512];
    
    // Check if the path is relative or absolute
    if (argv[1][0] != '/') {
        snprintf(path, sizeof(path), "./%s", argv[1]);
    } else {
        strncpy(path, argv[1], sizeof(path));
    }

    // verify that the executable exists and can be launch
    if (access(path, X_OK) == -1) {
        perror("Error during access");
        return EXIT_FAILURE;
    }

    printf("Executing fuzzer with %s\n", path);
    execute_fuzzer(path);

    return 0;
}
