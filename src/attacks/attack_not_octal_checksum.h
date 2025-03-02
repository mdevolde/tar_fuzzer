#ifndef ATTACK_NOT_OCTAL_CHECKSUM_H
#define ATTACK_NOT_OCTAL_CHECKSUM_H

/**
 * Create a TAR archive with non-octal checksum.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_not_octal_checksum(const char *output_filename, int index);

#endif /* ATTACK_NOT_OCTAL_CHECKSUM_H */
