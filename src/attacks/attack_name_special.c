#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_name_special.h"

void attack_name_special(const char *output_filename, int index) {
    const char *name_variations[] = {
        "file_with_*_wildcard.txt",
        "file_with_?.txt",
        "file_with_newline\n.txt",
        "Ωmega_file.txt",
        "你好世界.txt",
        "ファイル.txt",
        "file_with_\x7F_del.txt",
        "file_with_\x00_null.txt"
    };

    int num_variants = sizeof(name_variations) / sizeof(name_variations[0]);
    const char *corrupt_name = name_variations[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, corrupt_name, 1024);

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
