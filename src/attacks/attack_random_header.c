#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_random_header.h"

void attack_random_header(const char *output_filename, int index) {
    (void)index;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    memset(&header, rand() % 256, sizeof(header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
