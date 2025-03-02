#ifndef ATTACK_NON_NUMERIC_CHECKSUM_H
#define ATTACK_NON_NUMERIC_CHECKSUM_H

/**
 * Create a TAR archive with a non-numeric checksum.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_non_numeric_checksum(const char *output_filename, int index);

#endif /* ATTACK_NON_NUMERIC_CHECKSUM_H */
