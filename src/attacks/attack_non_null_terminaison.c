#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_non_null_terminaison.h"

void attack_non_null_terminaison(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    typedef enum {
        FIELD_CHECKSUM,
        FIELD_GID,
        FIELD_MODE,
        FIELD_MTIME,
        FIELD_UID,
        FIELD_NAME,
        FIELD_SIZE,
        FIELD_MAGIC,
        FIELD_UNAME,
        FIELD_GNAME,
        NUM_FIELDS,
    } TargetField;

    TargetField field = index % NUM_FIELDS;
    init_tar_header(&header, "test.txt", 1500);

    // Set a value but do not null-terminate it (all of these fields should be null-terminated)
    switch (field)
    {
    case FIELD_CHECKSUM:
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
    default:
        break;
    }
    
    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
