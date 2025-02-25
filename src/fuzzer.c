#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "fuzzer.h"
#include "tar_archive.h"

#include "attacks/attack_overflow.h"
#include "attacks/attack_wrong_checksum.h"
#include "attacks/attack_gid_corrupt.h"

#define RESULT_DIR "result/"

void ensure_result_dir() {
    struct stat st = {0};
    if (stat(RESULT_DIR, &st) == -1) {
        mkdir(RESULT_DIR, 0700);
    }
}

int execute_command(const char *executable, const char *tar_filename, int status) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error during pipe creation");
        return 0;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error during fork");
        return 0;
    }

    if (pid == 0) { 
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
        dup2(pipefd[1], STDERR_FILENO); // Redirect stderr to the pipe
        close(pipefd[1]);

        execlp(executable, executable, tar_filename, NULL);
        perror("Error during exec");
        exit(EXIT_FAILURE);
    } else { // Parent process
        close(pipefd[1]); // Close the write end of the pipe

        char output[1024] = {0};
        read(pipefd[0], output, sizeof(output) - 1);
        close(pipefd[0]);

        // verify that stdout contain "*** The program has crashed ***"
        if (strstr(output, "*** The program has crashed ***") != NULL) {
            char result_filename[256];
            snprintf(result_filename, sizeof(result_filename), "%s/success_%s_%d", RESULT_DIR, tar_filename, status);
            rename(tar_filename, result_filename);
            return 1;
        } else {
            remove(tar_filename);
            return 0;
        }
    }
}

void execute_fuzzer(const char *executable) {
    ensure_result_dir();

    attack_function attacks[] = {
        attack_overflow,
        attack_wrong_checksum,
        attack_gid_corrupt,
    };

    const char *attack_names[] = {
        "overflow",
        "wrong_checksum",
        "gid_corrupt",
    };

    const int number_per_attack[] = {
        1,
        10,
        14,
    };

    size_t attack_count = sizeof(attacks) / sizeof(attacks[0]);

    printf("-------------------------------\n");

    for (size_t i = 0; i < attack_count; i++) {
        int status = 0;
        for (int j = 0; j < number_per_attack[i]; j++) {    
            char tar_filename[256];
            snprintf(tar_filename, sizeof(tar_filename), "test_%s_%d.tar", attack_names[i], j);

            // Execute the attack, e.g.
            attacks[i](tar_filename, j);

            // Execute the command
            int current_status = execute_command(executable, tar_filename, j);
            status += current_status;
        }
        printf("Attack %s: %d/%d crashes\n", attack_names[i], status, number_per_attack[i]);
    }
}
