#ifndef ATTACK_ZERO_SIZE_FILE_H
#define ATTACK_ZERO_SIZE_FILE_H

#include <stdint.h>

/**
 * Create a TAR archive with a zero size file.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_zero_size_file(const char *output_filename, uint8_t index);

#endif /* ATTACK_ZERO_SIZE_FILE_H */
