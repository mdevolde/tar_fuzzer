#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_size_mismatch.h"

void attack_size_mismatch(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "size_mismatch.txt", 1024);

    snprintf(header.size, sizeof(header.size), "%011o", 512 * (index + 1));
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);

    char extra_data[TAR_BLOCK_SIZE * 2];
    memset(extra_data, 'X', sizeof(extra_data));

    if (index % 2 == 0) {
        add_tar_data_block(&archive, (const uint8_t *)extra_data, TAR_BLOCK_SIZE * 2);
    } else {
        finalize_tar_archive(&archive);
    }

    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
