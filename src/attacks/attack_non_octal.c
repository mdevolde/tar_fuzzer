#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "./attack_non_octal.h"

bool attack_non_octal(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1024);

    TargetField field = target_field_from_index(index);

    // Set numeric fields to a non-octal value (they should be octal)
    switch (field)
    {
    case FIELD_CHKSUM:
        snprintf(header.chksum, sizeof(header.chksum), "%07d", 9);
        break;
    case FIELD_GID:
        snprintf(header.gid, sizeof(header.gid), "%07d", 9);
        break;
    case FIELD_MODE:
        snprintf(header.mode, sizeof(header.mode), "%07d", 9);
        break;
    case FIELD_MTIME:
        snprintf(header.mtime, sizeof(header.mtime), "%011d", 9);
        break;
    case FIELD_SIZE:
        snprintf(header.size, sizeof(header.size), "%011d", 9);
        break;
    case FIELD_UID:
        snprintf(header.uid, sizeof(header.uid), "%07d", 9);
        break;
    default:
        is_header_tested = false;
        break;
    }

    if (field != FIELD_CHKSUM) {
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
    }

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return is_header_tested;
}
