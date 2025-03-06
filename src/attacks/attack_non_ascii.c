#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h" 
#include "attack_non_ascii.h"

bool attack_non_ascii(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    const char *not_ascii = "бк";

    tar_header header;
    init_tar_header(&header, "test.txt", 13);

    TargetField field = target_field_from_index(index);

    // Set a value with non-ASCII characters in such fields

    switch (field)
    {
    case FIELD_CHKSUM:
        snprintf(header.chksum, sizeof(header.chksum), "%s", not_ascii);
        break;
    case FIELD_GID:
        snprintf(header.gid, sizeof(header.gid), "%s", not_ascii);
        break;
    case FIELD_MODE:
        snprintf(header.mode, sizeof(header.mode), "%s", not_ascii);
        break;
    case FIELD_MTIME:
        snprintf(header.mtime, sizeof(header.mtime), "%s", not_ascii);
        break;
    case FIELD_UID:
        snprintf(header.uid, sizeof(header.uid), "%s", not_ascii);
        break;
    case FIELD_NAME:
        snprintf(header.name, sizeof(header.name), "%s", not_ascii);
        break;
    case FIELD_TYPEFLAG:
        header.typeflag = '\x7F';
        break;
    case FIELD_LINKNAME:
        snprintf(header.linkname, sizeof(header.linkname), "%s", not_ascii);
        break;
    case FIELD_MAGIC:
        snprintf(header.magic, sizeof(header.magic), "%s", not_ascii);
        break;
    case FIELD_VERSION:
        strncpy(header.version, not_ascii, sizeof(header.version));
        header.version[sizeof(header.version) - 1] = '\0';
        break;
    case FIELD_UNAME:
        snprintf(header.uname, sizeof(header.uname), "%s", not_ascii);
        break;
    case FIELD_GNAME:
        snprintf(header.gname, sizeof(header.gname), "%s", not_ascii);
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
