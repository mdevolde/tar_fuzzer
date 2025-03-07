#ifndef ATTACK_BAD_COMBO_TYPEFLAG_LINKNAME_H
#define ATTACK_BAD_COMBO_TYPEFLAG_LINKNAME_H

#include <stdint.h>

/**
 * Create a TAR archive with a bad combination of typeflag and linkname.
 * @param output_filename The name of the output file to generate.
 * @param index The index of the attack to perform.
 * @return True if a header has been tested, false otherwise.
 */
bool attack_bad_combo_typeflag_linkname(const char *output_filename, uint8_t index);

/** 
 * Return the tried combination of typeflag and linkname from the given index.
 * @param index The index of the attack to perform.
 * @return char* The combination of typeflag and linkname.
 */
char *combo_from_index(uint8_t index);

#endif /* ATTACK_BAD_COMBO_TYPEFLAG_LINKNAME_H */
