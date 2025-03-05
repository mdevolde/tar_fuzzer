#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_extra_padding.h"

void attack_extra_padding(const char *output_filename, int index) {
    (void)index;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "padded_file.txt", 100);
    add_tar_header(&archive, &header);

    uint8_t zero_block[TAR_BLOCK_SIZE] = {0};
    for (int i = 0; i < 10; i++) { 
        add_tar_data_block(&archive, zero_block, TAR_BLOCK_SIZE);
    }

    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
