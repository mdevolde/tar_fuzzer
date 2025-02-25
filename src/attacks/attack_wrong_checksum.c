#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_wrong_checksum.h"

void attack_wrong_checksum(const char *output_filename, int index) {
    if (index > 9) {
        return;
    }
    const char bad_chars[] = {'X', 'Z', '*', '?', '#', '!', '@', '&', '$', ' '};

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "wrong_checksum.txt", 1024);

    edit_tar_header_chksum(&header, bad_chars[index]);

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
