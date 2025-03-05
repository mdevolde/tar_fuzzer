#ifndef ATTACK_NON_ASCII_H
#define ATTACK_NON_ASCII_H

/**
 * Create a TAR archive with non-ASCII characters in different fields.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_non_ascii(const char *output_filename, int index);

#endif /* ATTACK_NON_ASCII_H */
