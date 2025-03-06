#ifndef ATTACK_END_OF_FILE_H
#define ATTACK_END_OF_FILE_H

#include <stdint.h>

/**
 * Create a TAR archive with strange EOF behavior.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_end_of_file(const char *output_filename, uint8_t index);

/** 
 * Return the EOF string from the given index.
 * @param index The index of the attack to perform.
 * @return char* The EOF string.
 */
char *eof_from_index(uint8_t index);

#endif /* ATTACK_END_OF_FILE_H */
