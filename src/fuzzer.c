#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include "fuzzer.h"
#include "tar_archive.h"

#include "attacks/attack_extreme.h"
#include "attacks/attack_unaligned_header.h"
#include "attacks/attack_early_eof.h"
#include "attacks/attack_duplicate_header.h"
#include "attacks/attack_multiple_files.h"
#include "attacks/attack_non_numeric.h"
#include "attacks/attack_non_ascii.h"
#include "attacks/attack_non_octal.h"
#include "attacks/attack_non_null_terminaison.h"
#include "attacks/attack_wrong_size.h"
#include "attacks/attack_negative_value.h"
#include "attacks/attack_recursive_symlink.h"
#include "attacks/attack_zero_size_file.h"
#include "attacks/attack_hardlink_to_missing_file.h"


int execute_command(const char *executable, const char *tar_filename) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error during pipe creation");
        return 0;
    }

    char files_before[100][256];
    int count_before = list_files(files_before, 100);
    qsort(files_before, count_before, 256, compare_filenames);

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

        char files_after[100][256];
        int count_after = list_files(files_after, 100);
        qsort(files_after, count_after, 256, compare_filenames);

        for (int i = 0; i < count_after; i++) {
            if (bsearch(files_after[i], files_before, count_before, 256, compare_filenames) == NULL) {
                if (strstr(files_after[i], ".tar") == NULL) {
                    remove(files_after[i]);
                }
            }
        }

        // Print the stdout of the program
        //printf("%s\n", output);

        // verify that stdout contain "*** The program has crashed ***"
        if (strstr(output, "*** The program has crashed ***") != NULL) {
            char result_filename[256];
            snprintf(result_filename, sizeof(result_filename), "success_%s", tar_filename);
            rename(tar_filename, result_filename);
            return 1;
        } else {
            remove(tar_filename);
            return 0;
        }
    }
}

int list_files(char filenames[][256], int max_files) {
    DIR *dir = opendir(".");
    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < max_files) {
        struct stat path_stat;
        if (stat(entry->d_name, &path_stat) == 0 && S_ISREG(path_stat.st_mode)) { 
            strncpy(filenames[count], entry->d_name, 255);
            filenames[count][255] = '\0';
            count++;
        }
    }

    closedir(dir);
    return count;
}

int compare_filenames(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

void execute_fuzzer(const char *executable) {
    // Clean up the directory
    system("rm -f *.tar");

    attack_function attacks[] = {
        attack_extreme,
        attack_unaligned_header,
        attack_early_eof,
        attack_duplicate_header,
        attack_multiple_files,
        attack_non_numeric,
        attack_non_ascii,
        attack_non_octal,
        attack_non_null_terminaison,
        attack_wrong_size,
        attack_negative_value,
        attack_recursive_symlink,
        attack_zero_size_file,
        attack_hardlink_to_missing_file
    };

    const char *attack_names[] = {
        "extreme",
        "unaligned_header",
        "early_eof",
        "duplicate_header",
        "multiple_files",
        "non_numeric",
        "non_ascii",
        "non_octal",
        "non_null_terminaison",
        "wrong_size",
        "negative_value",
        "recursive_symlink",
        "zero_size_file",
        "hardlink_to_missing_file"
    };

    const int number_per_attack[] = {
        5,
        1,
        1,
        1,
        1,
        6,
        8,
        6,
        10,
        10,
        5,
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
    printf("-------------------------------\n");
    printf("Total crashes: %d\n", total_crashes);
    printf("-------------------------------\n");
}
