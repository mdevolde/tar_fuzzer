#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "./attack_non_octal.h"

void attack_non_octal(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1024);

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

    switch (field)
    {
    case FIELD_CHECKSUM:
        snprintf(header.chksum, sizeof(header.chksum), "%07d", 9);
        break;
    case FIELD_GID:
        snprintf(header.gid, sizeof(header.gid), "%07d", 9);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MODE:
        snprintf(header.mode, sizeof(header.mode), "%07d", 9);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MTIME:
        snprintf(header.mtime, sizeof(header.mtime), "%011d", 9);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_SIZE:
        snprintf(header.size, sizeof(header.size), "%011d", 9);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UID:
        snprintf(header.uid, sizeof(header.uid), "%07d", 9);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
    default:
        break;
    }

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
