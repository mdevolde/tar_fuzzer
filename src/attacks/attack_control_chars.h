#ifndef ATTACK_CONTROL_CHARS_H
#define ATTACK_CONTROL_CHARS_H

/**
 * Create a TAR archive with control characters in a specific field.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_control_chars(const char *output_filename, int index);

#endif /* ATTACK_CONTROL_CHARS_H */
