#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_unaligned_header.h"

void attack_unaligned_header(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    memset(&header, 0, sizeof(header));
    snprintf(header.name, sizeof(header.name), "unaligned_%d.txt", index);
    snprintf(header.size, sizeof(header.size), "%011o", 512);

    uint8_t misaligned_data[TAR_BLOCK_SIZE + 1];
    memcpy(misaligned_data + 1, &header, sizeof(header));

    add_tar_data_block(&archive, misaligned_data, sizeof(misaligned_data));
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
