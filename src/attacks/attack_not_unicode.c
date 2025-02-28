#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_not_unicode.h"

void attack_not_unicode(const char *output_filename, int index) {
    const char non_unicode_variants[][TAR_NAME_SIZE] = {
        "\x7F" "DEL_character.txt",
        "\x1B" "ESC_sequence.txt",
        "\x08" "Backspace.txt",
        "\x0A" "Newline.txt",
        "\x0D" "CarriageReturn.txt",
        "\x00" "NullByte.txt",
        "Binary_\x80\x81\x82.txt",
        "Garbage_\xFE\xFF.txt"
    };

    int num_variants = sizeof(non_unicode_variants) / sizeof(non_unicode_variants[0]);
    const char *corrupt_name = non_unicode_variants[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, corrupt_name, 1024);

    strncpy(header.uname, corrupt_name, sizeof(header.uname) - 1);
    header.uname[sizeof(header.uname) - 1] = '\0';

    strncpy(header.gname, corrupt_name, sizeof(header.gname) - 1);
    header.gname[sizeof(header.gname) - 1] = '\0';


    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
