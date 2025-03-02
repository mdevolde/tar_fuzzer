#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_not_ascii_typeflag.h"

void attack_not_ascii_typeflag(const char *output_filename, int index) {
    (void)index;

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "typeflag_test.txt", 13);

    header.typeflag = '\x7F';

    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
    
    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
