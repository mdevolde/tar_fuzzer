#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_not_ascii_name.h"

void attack_not_ascii_name(const char *output_filename, int index) {
    const char *non_ascii_variants[] = {
        "éçàñ.txt",
        "Ωmega.txt",
        "你好世界.txt",
        "ファイル.txt",
        "🎉test.txt",
        "Müller.txt",
        "عربي.txt",
        "русский.txt"
    };

    int num_variants = sizeof(non_ascii_variants) / sizeof(non_ascii_variants[0]);
    const char *corrupt_name = non_ascii_variants[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, corrupt_name, 1024);

    snprintf(header.uname, sizeof(header.uname), "%s", corrupt_name);
    snprintf(header.gname, sizeof(header.gname), "%s", corrupt_name);
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
