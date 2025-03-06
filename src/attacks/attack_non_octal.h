#ifndef ATTACK_NON_OCTAL_H
#define ATTACK_NON_OCTAL_H

#include <stdint.h>

/**
 * Create a TAR archive with non-octal in different fields.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_non_octal(const char *output_filename, uint8_t index);

#endif /* ATTACK_NON_OCTAL_H */
