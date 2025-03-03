#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_non_numeric.h"

void attack_non_numeric(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1024);

    const char *non_numeric_string = "IAmANonNumericStringAndItWillCrash";

    typedef enum {
        FIELD_CHECKSUM,
        FIELD_GID,
        FIELD_MODE,
        FIELD_MTIME,
        FIELD_SIZE,
        FIELD_UID,
        NUM_FIELDS
    } TargetField;

    TargetField field = index % NUM_FIELDS;

    switch (field) {
    case FIELD_GID:
        strncpy(header.gid, non_numeric_string, 7);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MODE:
        strncpy(header.mode, non_numeric_string, 7);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MTIME:
        strncpy(header.mtime, non_numeric_string, 11);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_SIZE:
        strncpy(header.size, non_numeric_string, 11);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UID:
        strncpy(header.uid, non_numeric_string, 7);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_CHECKSUM:
        strncpy(header.chksum, non_numeric_string, 7);
        break;
    default:
        break;
    }

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
