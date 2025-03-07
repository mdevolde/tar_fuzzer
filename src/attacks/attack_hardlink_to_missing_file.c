#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_hardlink_to_missing_file.h"

bool attack_hardlink_to_missing_file(const char *output_filename, uint8_t index) {
    (void)index;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "hardlink", 0);
    // Set the typeflag to '1' to indicate a hard link
    header.typeflag = '1';
    // Set the linkname to a non-existing file
    snprintf(header.linkname, sizeof(header.linkname), "missing_file.txt");

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return true;
}
