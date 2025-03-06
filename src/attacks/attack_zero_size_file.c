#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_zero_size_file.h"

bool attack_zero_size_file(const char *output_filename, uint8_t index) {
    (void)index;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "zero_file.txt", 0);
    add_tar_header(&archive, &header);

    // Add data to the archive which is supposed to be zero size 
    const uint8_t extra_data[] = "Extra data";
    add_tar_data_block(&archive, extra_data, sizeof(extra_data));

    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return true;
}
