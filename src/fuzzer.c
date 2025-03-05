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

#include "attacks/attack_wrong_checksum.h"
#include "attacks/attack_name_special.h"
#include "attacks/attack_mtime_extreme.h"
#include "attacks/attack_size_mismatch.h"
#include "attacks/attack_linkname_invalid.h"
#include "attacks/attack_prefix_invalid.h"
#include "attacks/attack_unaligned_header.h"
#include "attacks/attack_early_eof.h"
#include "attacks/attack_duplicate_header.h"
#include "attacks/attack_random_header.h"
#include "attacks/attack_multiple_files.h"
#include "attacks/attack_non_numeric.h"
#include "attacks/attack_non_ascii.h"
#include "attacks/attack_non_octal.h"
#include "attacks/attack_non_null_terminaison.h"
#include "attacks/attack_wrong_size.h"
#include "attacks/attack_negative_value.h"
#include "attacks/attack_recursive_symlink.h"
#include "attacks/attack_zero_size_file.h"
#include "attacks/attack_extra_padding.h"
#include "attacks/attack_hardlink_to_missing_file.h"



#define RESULT_DIR "result/"

void ensure_result_dir() {
    struct stat st = {0};
    if (stat(RESULT_DIR, &st) == -1) {
        mkdir(RESULT_DIR, 0700);
    }
}

int execute_command(const char *executable, const char *tar_filename) {
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

        // Print the stdout of the program
        //printf("%s\n", output);

        // verify that stdout contain "*** The program has crashed ***"
        if (strstr(output, "*** The program has crashed ***") != NULL) {
            char result_filename[256];
            snprintf(result_filename, sizeof(result_filename), "%s/success_%s", RESULT_DIR, tar_filename);
            rename(tar_filename, result_filename);
            return 1;
        } else {
            if (strcmp(tar_filename, "test_not_ascii_gid_0.tar")) {} else {
                return 0;
            }
            remove(tar_filename);
            return 0;
        }
    }
}

void execute_fuzzer(const char *executable) {
    ensure_result_dir();

    // Clean up result directory
    system("rm -f result/*");

    attack_function attacks[] = {
        attack_wrong_checksum,
        attack_name_special,
        attack_mtime_extreme,
        attack_size_mismatch,
        attack_linkname_invalid,
        attack_prefix_invalid,
        attack_unaligned_header,
        attack_early_eof,
        attack_duplicate_header,
        attack_random_header,
        attack_multiple_files,
        attack_non_numeric,
        attack_non_ascii,
        attack_non_octal,
        attack_non_null_terminaison,
        attack_wrong_size,
        attack_negative_value,
        attack_recursive_symlink,
        attack_zero_size_file,
        attack_extra_padding,
        attack_hardlink_to_missing_file
    };

    const char *attack_names[] = {
        "wrong_checksum",
        "name_special",
        "mtime_extreme",
        "size_mismatch",
        "linkname_invalid",
        "prefix_invalid",
        "unaligned_header",
        "early_eof",
        "duplicate_header",
        "random_header",
        "multiple_files",
        "non_numeric",
        "non_ascii",
        "non_octal",
        "non_null_terminaison",
        "wrong_size",
        "negative_value",
        "recursive_symlink",
        "zero_size_file",
        "extra_padding",
        "hardlink_to_missing_file"
    };

    const int number_per_attack[] = {
        10,
        8,
        8,
        2,
        6,
        5,
        1,
        1,
        5,
        5,
        1,
        6,
        8,
        6,
        10,
        10,
        5,
        1,
        1,
        1,
        1
    };
    
    int total_crashes = 0;
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
            int current_status = execute_command(executable, tar_filename);
            status += current_status;
            total_crashes += current_status;
        }
        printf("Attack %s: %d/%d crashes\n\n", attack_names[i], status, number_per_attack[i]);
    }

    // Clean up
    system("find . -type f ! -name '*.tar' ! -name '*.c' ! -name '*.h' ! -name 'Makefile' ! -name 'README.md' ! -name 'fuzzer' ! -name 'fuzzer_test' ! -name 'extractor*' -delete");
    printf("-------------------------------\n");
    printf("Total crashes: %d\n", total_crashes);
    printf("-------------------------------\n");
}
