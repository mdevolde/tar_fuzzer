#ifndef ATTACK_EARLY_EOF_H
#define ATTACK_EARLY_EOF_H

#include <stdint.h>

/**
 * Create a TAR archive with an early EOF.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_early_eof(const char *output_filename, uint8_t index);

#endif /* ATTACK_EARLY_EOF_H */
