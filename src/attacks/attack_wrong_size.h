#ifndef ATTACK_WRONG_SIZE_H
#define ATTACK_WRONG_SIZE_H

#include <stdint.h>

/**
 * Create a TAR archive with a wrong size for a header.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_wrong_size(const char *output_filename, uint8_t index);

#endif /* ATTACK_WRONG_SIZE_H */
