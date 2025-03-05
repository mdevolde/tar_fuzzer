#ifndef ATTACK_HARDLINK_TO_MISSING_FILE_H
#define ATTACK_HARDLINK_TO_MISSING_FILE_H

/**
 * Create a TAR archive with a hardlink to a missing file.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_hardlink_to_missing_file(const char *output_filename, int index);

#endif /* ATTACK_HARDLINK_TO_MISSING_FILE_H */
