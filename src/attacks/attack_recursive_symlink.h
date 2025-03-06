#ifndef ATTACK_RECURSIVE_SYMLINK_H
#define ATTACK_RECURSIVE_SYMLINK_H

#include <stdint.h>

/**
 * Create a TAR archive with a recursive symlink.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_recursive_symlink(const char *output_filename, uint8_t index);

#endif /* ATTACK_RECURSIVE_SYMLINK_H */