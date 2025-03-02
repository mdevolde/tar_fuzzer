#ifndef ATTACK_NOT_ASCII_LINKNAME_H
#define ATTACK_NOT_ASCII_LINKNAME_H

/**
 * Create a TAR archive with a non-ASCII linkname.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_not_ascii_linkname(const char *output_filename, int index);

#endif /* ATTACK_NOT_ASCII_LINKNAME_H */
