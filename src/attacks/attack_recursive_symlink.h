#ifndef ATTACK_RECURSIVE_SYMLINK_H
#define ATTACK_RECURSIVE_SYMLINK_H

/**
 * Create a TAR archive with a recursive symlink.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_recursive_symlink(const char *output_filename, int index);

#endif /* ATTACK_RECURSIVE_SYMLINK_H */