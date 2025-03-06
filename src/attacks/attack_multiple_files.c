#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_multiple_files.h"

bool attack_multiple_files(const char *output_filename, uint8_t index) {
    (void)index;

    tar_archive archive;
    init_tar_archive(&archive);

    const char *filenames[] = {
        "file1.txt",
        "file2.txt",
        "duplicate.txt",
        "random.bin",
        "special_éçà.txt",
        "file_with_null_\x00.txt",
        "overflow_name_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt"
    };
    
    const uint16_t sizes[] = {50, 100, 2048, 512, 0, 1024, 4096};

    uint8_t num_files = sizeof(filenames) / sizeof(filenames[0]);

    // Add multiple files to the archive
    for (uint8_t i = 0; i < num_files; i++) {
        tar_header header;
        init_tar_header(&header, filenames[i], sizes[i]);

        if (i == 2) {
            snprintf(header.name, sizeof(header.name), "duplicate.txt");
        }
        
        edit_tar_header_chksum(&header, calculate_tar_checksum(&header));
        add_tar_header(&archive, &header);

        uint8_t *data = malloc(sizes[i]);
        if (data) {
            memset(data, 'A' + i, sizes[i]);
            add_tar_data_block(&archive, data, sizes[i]);
            free(data);
        }
    }

    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return true;
}
