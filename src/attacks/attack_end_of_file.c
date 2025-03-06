#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_end_of_file.h"

bool attack_end_of_file(const char *output_filename, uint8_t index) {
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "end_of_file_test.txt", 1024);

    static const size_t end_sizes[] = {
        0, 1, TAR_BLOCK_SIZE / 4, TAR_BLOCK_SIZE / 2, TAR_BLOCK_SIZE - 1,
        TAR_BLOCK_SIZE, TAR_BLOCK_SIZE + 1, TAR_BLOCK_SIZE * 2, TAR_BLOCK_SIZE * 4
    };

    size_t num_sizes = sizeof(end_sizes) / sizeof(end_sizes[0]);
    size_t end_size = end_sizes[index % num_sizes];

    char *end_data = calloc(1, end_size);  // Dynamically allocate the data
    if (!end_data) return false;

    add_tar_header(&archive, &header);

    // Add the file content
    const char file_content[] = "Testing end-of-file behavior!";
    add_tar_data_block(&archive, (const uint8_t *)file_content, sizeof(file_content) - 1);

    // If the index is even, add a padding to the file size
    if (index % 2 == 0) {
        snprintf(header.size, sizeof(header.size), "%011o", (unsigned int)(sizeof(file_content) + (index % 3 ? 100 : -100)));
    }

    // Add the end of the file
    add_tar_data_block(&archive, (const uint8_t *)end_data, end_size);

    // Special case for the second file (if index is)
    if (index >= num_sizes / 2) {
        tar_header header2;
        init_tar_header(&header2, "end_of_file_second.txt", 512);
        add_tar_header(&archive, &header2);
        const char second_content[] = "Second file content!";
        add_tar_data_block(&archive, (const uint8_t *)second_content, sizeof(second_content) - 1);
        add_tar_data_block(&archive, (const uint8_t *)end_data, end_size / 2); // Different size
    }

    free(end_data);

    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return true;
}

char *eof_from_index(uint8_t index) {
    switch (index)
    {
    case 0:
        return "NO_EOF";
    case 1:
        return "AFTER_1_BYTE";
    case 2:
        return "AFTER_128_BYTES";
    case 3:
        return "AFTER_256_BYTES";
    case 4:
        return "AFTER_511_BYTES";
    case 5:
        return "AFTER_512_BYTES";
    case 6:
        return "AFTER_513_BYTES";
    case 7:
        return "AFTER_1024_BYTES";
    case 8:
        return "AFTER_2048_BYTES";
    case 9:
        return "AFTER_4096_BYTES";
    case 10:
        return "AFTER_8192_BYTES";
    case 11:
        return "AFTER_16384_BYTES";
    default:
        return "UNKNOWN";
    }
}
