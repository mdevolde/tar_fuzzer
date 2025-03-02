#ifndef ATTACK_NOT_ASCII_MTIME_H
#define ATTACK_NOT_ASCII_MTIME_H

/**
 * Create a TAR archive with a non-ASCII mtime.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_not_ascii_mtime(const char *output_filename, int index);

#endif /* ATTACK_NOT_ASCII_MTIME_H */
