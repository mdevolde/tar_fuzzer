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

#define RESULT_DIR "result/"

void ensure_result_dir() {
    struct stat st = {0};
    if (stat(RESULT_DIR, &st) == -1) {
        mkdir(RESULT_DIR, 0700);
    }
}

void execute_command(const char *executable, const char *tar_filename) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error during pipe creation");
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error during fork");
        return;
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

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            char result_filename[256];
            snprintf(result_filename, sizeof(result_filename), "%s/success_%s", RESULT_DIR, tar_filename);
            rename(tar_filename, result_filename);
        } else {
            remove(tar_filename);
        }
    }
}

void execute_fuzzer(const char *executable) {
    ensure_result_dir();

    attack_function attacks[] = {
        attack_overflow,
    };

    const char *attack_names[] = {
        "overflow",
    };

    size_t attack_count = sizeof(attacks) / sizeof(attacks[0]);

    for (size_t i = 0; i < attack_count; i++) {
        char tar_filename[256];
        snprintf(tar_filename, sizeof(tar_filename), "test_%s.tar", attack_names[i]);

        // Execute the attack, e.g.
        attacks[i](tar_filename);

        // Execute the command
        execute_command(executable, tar_filename);
    }
}
