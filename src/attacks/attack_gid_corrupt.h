#ifndef ATTACK_GID_CORRUPT_H
#define ATTACK_GID_CORRUPT_H

/**
 * Create a TAR archive with a GID field corrupted.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_gid_corrupt(const char *output_filename, int index);

#endif /* ATTACK_GID_CORRUPT_H */
