#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_control_chars.h"

void attack_control_chars(const char *output_filename, int index) {
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
        snprintf(header.uname, sizeof(header.uname), "%s", injected_value);
        break;
    case FIELD_GNAME:
        snprintf(header.gname, sizeof(header.gname), "%s", injected_value);
        break;
    default:
        return;
    }

    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
