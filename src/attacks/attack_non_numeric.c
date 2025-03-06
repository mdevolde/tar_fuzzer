#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h" 
#include "attack_non_numeric.h"

bool attack_non_numeric(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1024);

    TargetField field = target_field_from_index(index);

    size_t slice_size;
    const char *non_numeric_string = "IAmANonNumericStringAndItWillCrash";
    const char *non_numeric_string_slice;

    // Set numeric fields to a non-numeric value (they should be numeric)
    switch (field) {
    case FIELD_GID:
        slice_size = sizeof(header.gid) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.gid, 0, sizeof(header.gid));
        memcpy(header.gid, non_numeric_string_slice, slice_size);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MODE:
        slice_size = sizeof(header.mode) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.mode, 0, sizeof(header.mode));
        memcpy(header.mode, non_numeric_string_slice, slice_size);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_MTIME:
        slice_size = sizeof(header.mtime) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.mtime, 0, sizeof(header.mtime));
        memcpy(header.mtime, non_numeric_string_slice, slice_size);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_SIZE:
        slice_size = sizeof(header.size) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.size, 0, sizeof(header.size));
        memcpy(header.size, non_numeric_string_slice, slice_size);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_UID:
        slice_size = sizeof(header.uid) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.uid, 0, sizeof(header.uid));
        memcpy(header.uid, non_numeric_string_slice, slice_size);
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        break;
    case FIELD_CHKSUM:
        slice_size = sizeof(header.chksum) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.chksum, 0, sizeof(header.chksum));
        memcpy(header.chksum, non_numeric_string_slice, slice_size);
        break;
    case FIELD_VERSION:
        slice_size = sizeof(header.version) - 1;
        non_numeric_string_slice = non_numeric_string;
        memset(header.version, 0, sizeof(header.version));
        memcpy(header.version, non_numeric_string_slice, slice_size);
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
