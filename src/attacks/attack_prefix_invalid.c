#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_prefix_invalid.h"

void attack_prefix_invalid(const char *output_filename, int index) {
    const char *prefix_variations[] = {
        "/",
        "..",
        "etc",
        "\xFF\xFF\xFF\xFF",
        "A_A_A_A_A_A_A_A_A_A_A_A_A_A_A_A"
    };

    int num_variants = sizeof(prefix_variations) / sizeof(prefix_variations[0]);
    const char *corrupt_prefix = prefix_variations[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "prefix_test.txt", 1024);
    
    snprintf(header.prefix, sizeof(header.prefix), "%s", corrupt_prefix);
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
