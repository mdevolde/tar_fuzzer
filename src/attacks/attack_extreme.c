#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_extreme.h"

bool attack_extreme(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "mtime_test.txt", 1024);

    TargetField field = target_field_from_index(index);
    unsigned long corrupt_value = (field == FIELD_SIZE || field == FIELD_MTIME) 
                                  ? 077777777777   // Max in octal for size, mtime
                                  : 07777777;      // Max in octal for mode, uid, gid

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat-truncation"

    // Set numeric fields to an extreme value
    switch (field)
    {
    case FIELD_MODE:
        snprintf(header.mode, sizeof(header.mode), "%07o", (unsigned int)corrupt_value);
        break;
    case FIELD_UID:
        snprintf(header.uid, sizeof(header.uid), "%07o", (unsigned int)corrupt_value);
        break;
    case FIELD_GID:
        snprintf(header.gid, sizeof(header.gid), "%07o", (unsigned int)corrupt_value);
        break;
    case FIELD_SIZE:
        snprintf(header.size, sizeof(header.size) , "%011lo", corrupt_value);
        break;
    case FIELD_MTIME:
        snprintf(header.mtime, sizeof(header.mtime), "%011lo", corrupt_value);
        break;
    default:
        is_header_tested = false;
        break;
    }

    #pragma GCC diagnostic pop
    
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return is_header_tested;
}
