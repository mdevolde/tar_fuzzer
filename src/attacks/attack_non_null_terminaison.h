#ifndef ATTACK_NON_NULL_TERMINAISON_H
#define ATTACK_NON_NULL_TERMINAISON_H

/**
 * Create a TAR archive with missing null terminaison in different fields.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return void
 */
void attack_non_null_terminaison(const char *output_filename, int index);

#endif /* ATTACK_NON_NULL_TERMINAISON_H */
