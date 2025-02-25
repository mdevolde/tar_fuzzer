#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_gid_corrupt.h"

void attack_gid_corrupt(const char *output_filename, int index) {
    if (index > 13) {
        return;
    }
    const char gid_values[][8] = {
        "0000000",  // GID normal
        "7777777",  // Max en octal
        "9999999",  // Hors plage octale
        "00000\0\0", // Partiellement null-terminated
        "  1000 ",  // Padding d'espaces
        "1 00000",  // Espace dans le GID
        "1000\t",   // Tabulation
        "1000\n",   // Saut de ligne
        "10000000", // Trop long
        "999",      // Trop court
        "root",     // Nom au lieu d'un nombre
        "\xff\xff\xff\xff\xff\xff\xff", // Valeurs binaires invalides
        " \0\0\0\0\0\0", // Espace suivi de `\0`
        "1000\x7F"  // Caractère `DEL` (`\x7F`)
    };

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "gid_corrupt.txt", 1024);

    edit_tar_header_gid(&header, gid_values[index]);

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
