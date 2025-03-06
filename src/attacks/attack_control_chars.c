#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_control_chars.h"

bool attack_control_chars(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "test.txt", 1024);

    TargetField field = target_field_from_index(index);

    char special_chars[] = {'\a', '\b', '\n', '\r', '\t', '\v', '\f', '\x1B'};
    char injected_value[TAR_NAME_SIZE];
    memset(injected_value, special_chars[index % sizeof(special_chars)], sizeof(injected_value));
    injected_value[sizeof(injected_value) - 1] = '\0';

    switch (field) {
    case FIELD_NAME:
        snprintf(header.name, sizeof(header.name), "%s", injected_value);
        break;
    case FIELD_UNAME:
        strncpy(header.uname, injected_value, sizeof(header.uname));
        header.uname[sizeof(header.uname) - 1] = '\0';
        break;
    case FIELD_GNAME:
        strncpy(header.gname, injected_value, sizeof(header.gname));
        header.gname[sizeof(header.gname) - 1] = '\0';
        break;
    default:
        is_header_tested = false;
        break;
    }

    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
    
    return is_header_tested;
}
