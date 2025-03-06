#ifndef FUZZER_H
#define FUZZER_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Function pointer type for an attack function.
 * @param output_filename The name of the output file to generate.
 * @param index The current index of the command.
 * @return True if a header has been tested, false otherwise.
 */
typedef bool (*attack_function)(const char *output_filename, uint8_t index);

/* Enumeration to define the type of execution. */
typedef enum {
    SIMPLE_EXEC,                // Execute the attack once
    MULTIPLE_EXEC_FIELD,        // Execute the attack multiple times with different fields
    MULTIPLE_EXEC_COMBINATIONS, // Execute the attack multiple times with different combinations in the same field
    MULTIPLE_EXEC_EOF           // Execute the attack multiple times with different EOF

} execution_type;

/* Structure to store information about an attack. */
typedef struct {
    const char *name;            // Name of the attack
    attack_function function;    // Pointer to the attack function
    execution_type type_of_exec; // Type of execution
} attack_t;

/**
 * List all files in the current directory.
 * @param filenames The array to store the filenames.
 * @param max_files The maximum number of files to store.
 * @return uint8_t The number of files found.
 */
uint8_t list_files(char filenames[][256], uint8_t max_files);

/**
 * Compare two filenames for sorting.
 * @param a The first filename.
 * @param b The second filename.
 * @return int The comparison result.
 */
int compare_filenames(const void *a, const void *b);

/**
 * Execute the fuzzer with the given executable.
 * @param executable The name of the executable to test.
 * @return 1 if the fuzzer found crashes, 0 otherwise.
 */
int execute_fuzzer(const char *executable);


#endif /* FUZZER_H */
