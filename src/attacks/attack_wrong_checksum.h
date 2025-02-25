#ifndef ATTACK_WRONG_CHECKSUM_H
#define ATTACK_WRONG_CHECKSUM_H

/**
 * Create a TAR archive with a wrong checksum.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_wrong_checksum(const char *output_filename, int index);

#endif /* ATTACK_WRONG_CHECKSUM_H */
