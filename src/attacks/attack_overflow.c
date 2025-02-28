#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "attack_overflow.h"

void attack_overflow(const char *output_filename, int index) {
    char long_name[TAR_NAME_SIZE + 50];

    memset(long_name, 'A' + (index % 26), sizeof(long_name) - 1);
    long_name[sizeof(long_name) - 1] = '\0';

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, long_name, 1024);

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
