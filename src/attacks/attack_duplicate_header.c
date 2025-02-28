#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_duplicate_header.h"

void attack_duplicate_header(const char *output_filename, int index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "duplicate.txt", 1024);

    add_tar_header(&archive, &header);
    

    int num_duplicates = (index % 5) + 2;
    for (int i = 0; i < num_duplicates; i++) {
        add_tar_header(&archive, &header);
    }
    
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
