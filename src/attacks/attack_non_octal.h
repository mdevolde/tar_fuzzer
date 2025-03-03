#ifndef ATTACK_NON_OCTAL_H
#define ATTACK_NON_OCTAL_H

/**
 * Create a TAR archive with non-octal in different fields.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_non_octal(const char *output_filename, int index);

#endif /* ATTACK_NON_OCTAL_H */
