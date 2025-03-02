#ifndef ATTACK_NON_NUMERIC_GID_H
#define ATTACK_NON_NUMERIC_GID_H

/**
 * Create a TAR archive with a non-numeric GID.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_non_numeric_gid(const char *output_filename, int index);

#endif /* ATTACK_NON_NUMERIC_GID_H */
