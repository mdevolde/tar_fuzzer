#ifndef HEADER_FIELDS_H
#define HEADER_FIELDS_H

#include <stdint.h>

/* Enumerated type for the fields in the header of a tar file */
typedef enum {
    FIELD_NAME,
    FIELD_MODE,
    FIELD_UID,
    FIELD_GID,
    FIELD_SIZE,
    FIELD_MTIME,
    FIELD_TYPEFLAG,
    FIELD_MAGIC,
    FIELD_VERSION,
    FIELD_UNAME,
    FIELD_GNAME,
    FIELD_CHKSUM,
    FIELD_LINKNAME,
    NUM_FIELDS,
} TargetField;

/**
 * Get the target field from an index.
 * @param index The index of the field.
 * @return The target field.
 */
TargetField target_field_from_index(uint8_t index);

/** Convert an index to a string representation of the field.
 * 
 * @param index The index of the field.
 * @return The string representation of the field.
 */
const char *field_to_string(uint8_t index);

#endif /* HEADER_FIELDS_H */
