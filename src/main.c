#include <stdio.h>
#include <stdlib.h>
#include "fuzzer.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_executable>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // verify that the executable exists and can be launch
    if (access(argv[1], X_OK) == -1) {
        perror("Error during access");
        return EXIT_FAILURE;
    }

    printf("Executing fuzzer with %s\n", argv[1]);
    execute_fuzzer(argv[1]);

    return 0;
}
