#ifndef ATTACK_EMPTY_FIELD_H
#define ATTACK_EMPTY_FIELD_H

/**
 * Create a TAR archive with an empty field.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_empty_field(const char *output_filename, int index);

#endif /* ATTACK_EMPTY_FIELD_H */
