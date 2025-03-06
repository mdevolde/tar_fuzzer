#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h" 
#include "attack_non_null_terminaison.h"

bool attack_non_null_terminaison(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1500);

    TargetField field = target_field_from_index(index);

    // Set a value but do not null-terminate it (all of these fields should be null-terminated)
    switch (field)
    {
    case FIELD_CHKSUM:
        memset(header.chksum, ' ', sizeof(header.chksum));
        break;
    case FIELD_GID:
        memset(header.gid, ' ', sizeof(header.gid));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MODE:
        memset(header.mode, ' ', sizeof(header.mode));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MTIME:
        memset(header.mtime, ' ', sizeof(header.mtime));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UID:
        memset(header.uid, ' ', sizeof(header.uid));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_NAME:
        memset(header.name, ' ', sizeof(header.name));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_SIZE:
        memset(header.size, ' ', sizeof(header.size));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MAGIC:
        memset(header.magic, ' ', sizeof(header.magic));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UNAME:
        memset(header.uname, ' ', sizeof(header.uname));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_GNAME:
        memset(header.gname, ' ', sizeof(header.gname));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break; 
    case FIELD_VERSION:
        memset(header.version, ' ', sizeof(header.version));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_TYPEFLAG:
        header.typeflag = ' ';
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_LINKNAME:
        memset(header.linkname, ' ', sizeof(header.linkname));
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    default:
        is_header_tested = false;
        break;
    }
    
    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return is_header_tested;
}
