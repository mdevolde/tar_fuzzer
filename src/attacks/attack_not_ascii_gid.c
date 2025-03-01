#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_not_ascii.h"

void attack_not_ascii_gid(const char *output_filename, int index) {
    (void)index;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "hello.txt", 13);

    // Fill the GID field with non-ASCII characters
    snprintf(header.gid, sizeof(header.gid), "%s", "бк");
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);

    const uint8_t data[] = "Hello, World!";
    add_tar_data_block(&archive, data, 13);
    finalize_tar_archive(&archive);
    printf("Writing archive to %s\n", output_filename);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
