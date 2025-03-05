#ifndef FUZZER_H
#define FUZZER_H

/**
 * Function pointer type for an attack function.
 * @param output_filename The name of the output file to generate.
 * @param status The current index of the command.
 * @return void
 */
typedef void (*attack_function)(const char *output_filename, int status);

/**
 * Execute the command with the given executable and TAR filename.
 * @param executable The name of the executable to test.
 * @param tar_filename The name of the TAR file to use as input.
 * @return int The exit status of the command.
 */
int execute_command(const char *executable, const char *tar_filename);

/**
 * Execute the fuzzer with the given executable.
 * @param executable The name of the executable to test.
 * @return void
 */
void execute_fuzzer(const char *executable);


#endif /* FUZZER_H */
