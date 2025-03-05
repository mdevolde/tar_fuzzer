#ifndef ATTACK_DUPLICATE_HEADER_H
#define ATTACK_DUPLICATE_HEADER_H

/**
 * Create a TAR archive with a duplicate header.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_duplicate_header(const char *output_filename, int index);

#endif /* ATTACK_DUPLICATE_HEADER_H */
