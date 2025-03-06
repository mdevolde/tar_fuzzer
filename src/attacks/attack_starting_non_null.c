#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_starting_non_null.h"

bool attack_starting_non_null(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1024);

    TargetField field = target_field_from_index(index);

    // Character to put at the beginning of the field
    const char non_null_byte = '\x01';

    switch (field) {
    case FIELD_NAME:
        header.name[0] = non_null_byte;
        break;
    case FIELD_MODE:
        header.mode[0] = non_null_byte;
        break;
    case FIELD_UID:
        header.uid[0] = non_null_byte;
        break;
    case FIELD_GID:
        header.gid[0] = non_null_byte;
        break;
    case FIELD_SIZE:
        header.size[0] = non_null_byte;
        break;
    case FIELD_MTIME:
        header.mtime[0] = non_null_byte;
        break;
    case FIELD_CHKSUM:
        header.chksum[0] = non_null_byte;
        break;
    case FIELD_TYPEFLAG:
        header.typeflag = non_null_byte;
        break;
    case FIELD_LINKNAME:
        header.linkname[0] = non_null_byte;
        break;
    case FIELD_MAGIC:
        header.magic[0] = non_null_byte;
        break;
    case FIELD_VERSION:
        header.version[0] = non_null_byte;
        break;
    case FIELD_UNAME:
        header.uname[0] = non_null_byte;
        break;
    case FIELD_GNAME:
        header.gname[0] = non_null_byte;
        break;
    default:
        is_header_tested = false;
        break;
    }

    // Recalculate the checksum if the field is not the checksum itself
    if (field != FIELD_CHKSUM) {
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
    }

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return is_header_tested;
}
