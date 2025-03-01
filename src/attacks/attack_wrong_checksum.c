#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_wrong_checksum.h"

void attack_wrong_checksum(const char *output_filename, int index) {
    const char chksum_values[][8] = {
        "0000000",
        "9999999",
        "abcdefg",
        "      ",
        "!!!!!!!",
        "1234\n56",
        "\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
    };

    int num_variants = sizeof(chksum_values) / sizeof(chksum_values[0]);
    const char *corrupt_chksum = chksum_values[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "checksum_test.txt", 1024);
    
    memcpy(header.chksum, corrupt_chksum, sizeof(header.chksum));
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
