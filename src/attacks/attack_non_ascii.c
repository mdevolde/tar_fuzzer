#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h" 
#include "attack_non_ascii.h"

void attack_non_ascii(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    const char *not_ascii = "бк";

    tar_header header;
    memset(&header, 0, sizeof(header));

    TargetField field = target_field_from_index(index);

    // Set a value with non-ASCII characters in such fields
    switch (field)
    {
    case FIELD_CHKSUM:
        init_tar_header(&header, "chksum_test.txt", 13);
        snprintf(header.chksum, sizeof(header.chksum), "%s", not_ascii);
        break;
    case FIELD_GID:
        init_tar_header(&header, "gid_test.txt", 13);
        snprintf(header.gid, sizeof(header.gid), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MODE:
        init_tar_header(&header, "mode_test.txt", 13);
        snprintf(header.mode, sizeof(header.mode), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MTIME:
        init_tar_header(&header, "mtime_test.txt", 13);
        snprintf(header.mtime, sizeof(header.mtime), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UID:
        init_tar_header(&header, "uid_test.txt", 13);
        snprintf(header.uid, sizeof(header.uid), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_NAME:
        init_tar_header(&header, "name_test.txt", 13);
        snprintf(header.name, sizeof(header.name), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_TYPEFLAG:
        init_tar_header(&header, "typeflag_test.txt", 13);
        header.typeflag = '\x7F';
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_LINKNAME:
        init_tar_header(&header, "linkname_test.txt", 13);
        snprintf(header.linkname, sizeof(header.linkname), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MAGIC:
        init_tar_header(&header, "magic_test.txt", 13);
        snprintf(header.magic, sizeof(header.magic), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_VERSION:
        init_tar_header(&header, "version_test.txt", 13);
        snprintf(header.version, sizeof(header.version), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UNAME:
        init_tar_header(&header, "uname_test.txt", 13);
        snprintf(header.uname, sizeof(header.uname), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_GNAME:
        init_tar_header(&header, "gname_test.txt", 13);
        snprintf(header.gname, sizeof(header.gname), "%s", not_ascii);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    default:
        break;
    }
    
    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
