#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_mtime_extreme.h"

void attack_mtime_extreme(const char *output_filename, int index) {
    const long mtime_values[] = {
        0,        
        -300,    
        300,
        INT_MIN,
        INT_MAX,
        LLONG_MAX,
        9999999999L,
        1704067200L
    };

    int num_variants = sizeof(mtime_values) / sizeof(mtime_values[0]);
    long corrupt_mtime = mtime_values[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "mtime_test.txt", 1024);
    
    snprintf(header.mtime, sizeof(header.mtime), "%011o", (unsigned int)corrupt_mtime);

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
