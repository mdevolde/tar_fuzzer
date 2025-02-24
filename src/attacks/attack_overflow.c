#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "attack_overflow.h"

void attack_overflow(const char *output_filename) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "overflow.txt", 1024);

    // Overflow the name field
    memset(header.name, 'A', TAR_NAME_SIZE);
    header.name[TAR_NAME_SIZE - 1] = '\0';

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
