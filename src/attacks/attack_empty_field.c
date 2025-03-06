#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_empty_field.h"

bool attack_empty_field(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test_empty_field.txt", 1024);

    TargetField field = target_field_from_index(index);

    switch (field) {
    case FIELD_NAME:
        memset(header.name, 0, sizeof(header.name));
        break;
    case FIELD_MODE:
        memset(header.mode, 0, sizeof(header.mode));
        break;
    case FIELD_UID:
        memset(header.uid, 0, sizeof(header.uid));
        break;
    case FIELD_GID:
        memset(header.gid, 0, sizeof(header.gid));
        break;
    case FIELD_SIZE:
        memset(header.size, 0, sizeof(header.size));
        break;
    case FIELD_MTIME:
        memset(header.mtime, 0, sizeof(header.mtime));
        break;
    case FIELD_CHKSUM:
        memset(header.chksum, 0, sizeof(header.chksum));
        break;
    case FIELD_TYPEFLAG:
        memset(&header.typeflag, 0, sizeof(header.typeflag));
        break;
    case FIELD_LINKNAME:
        memset(header.linkname, 0, sizeof(header.linkname));
        break;
    case FIELD_MAGIC:
        memset(header.magic, 0, sizeof(header.magic));
        break;
    case FIELD_VERSION:
        memset(header.version, 0, sizeof(header.version));
        break;
    case FIELD_UNAME:
        memset(header.uname, 0, sizeof(header.uname));
        break;
    case FIELD_GNAME:
        memset(header.gname, 0, sizeof(header.gname));
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
