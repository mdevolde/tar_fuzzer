#ifndef ATTACK_OVERFLOW_H
#define ATTACK_OVERFLOW_H

/**
 * Create a TAR archive with a buffer overflow.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_overflow(const char *output_filename, int index);

#endif /* ATTACK_OVERFLOW_H */
