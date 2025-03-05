#ifndef ATTACK_MULTIPLE_FILES_H
#define ATTACK_MULTIPLE_FILES_H

/**
 * Create a TAR archive with multiple files.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_multiple_files(const char *output_filename, int index);

#endif /* ATTACK_MULTIPLE_FILES_H */
