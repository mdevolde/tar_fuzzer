#ifndef ATTACK_MTIME_EXTREME_H
#define ATTACK_MTIME_EXTREME_H

/**
 * Create a TAR archive with an extreme mtime.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_mtime_extreme(const char *output_filename, int index);

#endif /* ATTACK_MTIME_EXTREME_H */
