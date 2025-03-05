#include "header_fields.h"

TargetField target_field_from_index(uint8_t index) {
    return index % NUM_FIELDS;
}

const char *field_to_string(uint8_t index) {
    switch (index) {
        case 0: return "FIELD_NAME";
        case 1: return "FIELD_MODE";
        case 2: return "FIELD_UID";
        case 3: return "FIELD_GID";
        case 4: return "FIELD_SIZE";
        case 5: return "FIELD_MTIME";
        case 6: return "FIELD_TYPEFLAG";
        case 7: return "FIELD_MAGIC";
        case 8: return "FIELD_VERSION";
        case 9: return "FIELD_UNAME";
        case 10: return "FIELD_GNAME";
        case 11: return "FIELD_CHKSUM";
        default: return "UNKNOWN";
    }
} 
