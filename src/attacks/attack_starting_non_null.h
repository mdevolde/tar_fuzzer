#ifndef ATTACK_STARTING_NON_NULL_H
#define ATTACK_STARTING_NON_NULL_H

#include <stdint.h>

/**
 * Create a TAR archive with a non-null starting character.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_starting_non_null(const char *output_filename, uint8_t index);

#endif /* ATTACK_STARTING_NON_NULL_H */
