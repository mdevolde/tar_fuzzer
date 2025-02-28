#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_early_eof.h"

void attack_early_eof(const char *output_filename, int index) {
    (void)index;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "early_eof.txt", 1024);

    add_tar_header(&archive, &header);

    // Do not finalize the archive to create an early EOF
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
