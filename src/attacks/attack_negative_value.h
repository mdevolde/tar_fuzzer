#ifndef ATTACK_NEGATIVE_VALUE_H
#define ATTACK_NEGATIVE_VALUE_H

/**
 * Create a TAR archive with a negative value in a header field.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_negative_value(const char *output_filename, int index);

#endif /* ATTACK_NEGATIVE_VALUE_H */
