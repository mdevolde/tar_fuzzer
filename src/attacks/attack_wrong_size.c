#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_wrong_size.h"

bool attack_wrong_size(const char *output_filename, int index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1500);

    TargetField field = target_field_from_index(index);

    // Set a value with a different size than the expected one 
    switch (field)
    {
    case FIELD_CHKSUM:
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
