#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_negative_value.h"

void attack_negative_value(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    typedef enum {
        FIELD_MODE,
        FIELD_UID,
        FIELD_GID,
        FIELD_SIZE,
        FIELD_MTIME,
        NUM_FIELDS
    } TargetField;

    TargetField field = index % NUM_FIELDS;
    init_tar_header(&header, "test.txt", 1500);

    // Set numeric fields to a negative value (there is no reason for them to be negative)
    switch (field) {
        case FIELD_MODE:
            snprintf(header.mode, sizeof(header.mode) - 1, "-0755");
            break;
        case FIELD_UID:
            snprintf(header.uid, sizeof(header.uid) - 1, "-1000");
            break;
        case FIELD_GID:
            snprintf(header.gid, sizeof(header.gid) - 1, "-1000");
            break;
        case FIELD_SIZE:
            snprintf(header.size, sizeof(header.size) - 1, "-512");
            break;
        case FIELD_MTIME:
            snprintf(header.mtime, sizeof(header.mtime) - 1, "-167253120");
            break;
        default:
            break;
    }

    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
