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
#include "header_fields.h"

#include "attacks/attack_extreme.h"
#include "attacks/attack_unaligned_header.h"
#include "attacks/attack_end_of_file.h"
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
#include "attacks/attack_control_chars.h"
#include "attacks/attack_empty_field.h"
#include "attacks/attack_starting_non_null.h"
#include "attacks/attack_bad_combo_typeflag_linkname.h"


// Array of attacks to execute, with their name, function and if they need to be executed multiple times
// This array can be extended with new attacks
static const attack_t attacks[] = {
    {"extreme", attack_extreme, MULTIPLE_EXEC_FIELD},
    {"unaligned_header", attack_unaligned_header, SIMPLE_EXEC},
    {"early_eof", attack_end_of_file, MULTIPLE_EXEC_EOF},
    {"duplicate_header", attack_duplicate_header, SIMPLE_EXEC},
    {"multiple_files", attack_multiple_files, SIMPLE_EXEC},
    {"non_numeric", attack_non_numeric, MULTIPLE_EXEC_FIELD},
    {"non_ascii", attack_non_ascii, MULTIPLE_EXEC_FIELD},
    {"non_octal", attack_non_octal, MULTIPLE_EXEC_FIELD},
    {"non_null_terminaison", attack_non_null_terminaison, MULTIPLE_EXEC_FIELD},
    {"wrong_size", attack_wrong_size, MULTIPLE_EXEC_FIELD},
    {"negative_value", attack_negative_value, MULTIPLE_EXEC_FIELD},
    {"recursive_symlink", attack_recursive_symlink, SIMPLE_EXEC},
    {"zero_size_file", attack_zero_size_file, SIMPLE_EXEC},
    {"hardlink_to_missing_file", attack_hardlink_to_missing_file, SIMPLE_EXEC},
    {"control_chars", attack_control_chars, MULTIPLE_EXEC_FIELD},
    {"empty_field", attack_empty_field, MULTIPLE_EXEC_FIELD},
    {"starting_non_null", attack_starting_non_null, MULTIPLE_EXEC_FIELD},
    {"bad_combo_typeflag_linkname", attack_bad_combo_typeflag_linkname, MULTIPLE_EXEC_COMBINATIONS}
};

/**
 * Execute the command with the given executable and TAR filename.
 * @param executable The name of the executable to test.
 * @param tar_filename The name of the TAR file to use as input.
 * @return u_int8_t The exit status of the command.
 */
static uint8_t execute_command(const char *executable, const char *tar_filename) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error during pipe creation");
        return 0;
    }

    char files_before[100][256];
    uint8_t count_before = list_files(files_before, 100);
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
        uint8_t count_after = list_files(files_after, 100);
        qsort(files_after, count_after, 256, compare_filenames);

        for (uint8_t i = 0; i < count_after; i++) {
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

uint8_t list_files(char filenames[][256], uint8_t max_files) {
    DIR *dir = opendir(".");
    if (!dir) return 0;

    struct dirent *entry;
    uint8_t count = 0; // The maximum number of files is 255 because of the type of this variable

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
    
    uint16_t total_crashes = 0; // The maximum number of crashes is 65535 because of the type of this variable
    size_t attack_count = sizeof(attacks) / sizeof(attacks[0]);
    uint8_t total_attacks = 0;

    printf("-------------------------------\n");

    for (size_t i = 0; i < attack_count; i++) {
        uint8_t status = 0;
        uint8_t number_of_attacks = attacks[i].type_of_exec == SIMPLE_EXEC ? 1 : 12;
        uint8_t skip_attack = 0;
        for (uint8_t j = 0; j < number_of_attacks; j++) {    
            char tar_filename[256];
            if (attacks[i].type_of_exec == SIMPLE_EXEC)
                snprintf(tar_filename, sizeof(tar_filename), "test_%s.tar", attacks[i].name);
            else if (attacks[i].type_of_exec == MULTIPLE_EXEC_FIELD)
                snprintf(tar_filename, sizeof(tar_filename), "test_%s_in_%s.tar", attacks[i].name, field_to_string(j));
            else if (attacks[i].type_of_exec == MULTIPLE_EXEC_COMBINATIONS)
                snprintf(tar_filename, sizeof(tar_filename), "test_%s_WITH_%s.tar", attacks[i].name, combo_from_index(j));
            else if (attacks[i].type_of_exec == MULTIPLE_EXEC_EOF)
                snprintf(tar_filename, sizeof(tar_filename), "test_%s_EOF_%s.tar", attacks[i].name, eof_from_index(j));

            // Execute the attack, e.g.
            bool is_header_tested = attacks[i].function(tar_filename, j);
            if (!is_header_tested) {
                skip_attack++;
            } 

            // Execute the command
            uint8_t current_status = execute_command(executable, tar_filename);
            status += current_status;
            total_crashes += current_status;
        }
        
        // For testing case when the attack always works even when it's a skip attack
        if (status > number_of_attacks - skip_attack) {
            status = number_of_attacks - skip_attack;
        }
        total_attacks += status;
        printf("Attack %s: %d/%d crashes\n", attacks[i].name, status, number_of_attacks - skip_attack);

        // Check if there files with the attack name in and if so, print them with comma separation
        char files[100][256];
        uint8_t count = list_files(files, 100);
        uint8_t found = 0;

        for (uint8_t k = 0; k < count; k++) {
            if (strstr(files[k], attacks[i].name) != NULL) {
                if (found > 0) printf(", ");
                printf("%s", files[k]);
                found++;
            }
        }
        if (found > 0) printf("\n");
        printf("\n");
    }

    // For testing case when the total crashes is more than the total attacks because even a skip attack is counted as crash (the exec always crashes)
    if (total_crashes > total_attacks) {
        total_crashes = total_attacks;
    }

    // Clean up
    printf("-------------------------------\n");
    printf("Total crashes: %d\n", total_crashes);
    printf("-------------------------------\n");
}
