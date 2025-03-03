#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_non_ascii.h"

void attack_non_ascii(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    const char *not_ascii = "бк";

    tar_header header;
    typedef enum {
        FIELD_CHECKSUM,
        FIELD_GID,
        FIELD_MODE,
        FIELD_MTIME,
        FIELD_UID,
        FIELD_LINKNAME,
        FIELD_NAME,
        FIELD_TYPEFLAG,
        NUM_FIELDS,
    } TargetField;

    TargetField field = index % NUM_FIELDS;

    switch (field)
    {
    case FIELD_CHECKSUM:
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
    case FIELD_LINKNAME:
        init_tar_header(&header, "linkname_test.txt", 13);
        snprintf(header.linkname, sizeof(header.linkname), "%s", not_ascii);
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
    default:
        break;
    }
    
    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
