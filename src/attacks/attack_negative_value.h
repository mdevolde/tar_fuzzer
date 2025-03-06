#ifndef ATTACK_NEGATIVE_VALUE_H
#define ATTACK_NEGATIVE_VALUE_H

#include <stdint.h>

/**
 * Create a TAR archive with a negative value in a header field.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_negative_value(const char *output_filename, uint8_t index);

#endif /* ATTACK_NEGATIVE_VALUE_H */
