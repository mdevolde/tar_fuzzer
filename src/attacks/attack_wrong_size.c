#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_wrong_size.h"

void attack_wrong_size(const char *output_filename, int index) {
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

    // Set a value with a different size than the expected one 
    switch (field)
    {
    case FIELD_CHECKSUM:
        memset(header.chksum, ' ', sizeof(header.chksum));
        header.chksum[3] = '1';
        break;
    case FIELD_GID:
        memset(header.gid, ' ', sizeof(header.gid));
        header.gid[3] = '1';
        break;
    case FIELD_MODE:
        memset(header.mode, ' ', sizeof(header.mode));
        header.mode[3] = '1';
        break;
    case FIELD_MTIME:
        memset(header.mtime, ' ', sizeof(header.mtime));
        header.mtime[3] = '1';
        break;
    case FIELD_UID:
        memset(header.uid, ' ', sizeof(header.uid));
        header.uid[3] = '1';
        break;
    case FIELD_NAME:
        memset(header.name, ' ', sizeof(header.name));
        header.name[3] = 't';
        break;
    case FIELD_SIZE:
        memset(header.size, ' ', sizeof(header.size));
        header.size[3] = '1';
        break;
    case FIELD_MAGIC:
        memset(header.magic, ' ', sizeof(header.magic));
        header.magic[3] = 'u';
        break;
    case FIELD_UNAME:
        memset(header.uname, ' ', sizeof(header.uname));
        header.uname[3] = 'u';
        break;
    case FIELD_GNAME:
        memset(header.gname, ' ', sizeof(header.gname));
        header.gname[3] = 'g';
        break; 
    default:
        break;
    }

    if (field != FIELD_CHECKSUM) {
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
    } 

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
