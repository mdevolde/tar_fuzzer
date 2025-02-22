#ifndef TAR_ARCHIVE_H
#define TAR_ARCHIVE_H

#include <stdint.h>
#include <stdlib.h>
#include "tar_header.h"

#define TAR_BLOCK_SIZE 512

/* Stuct representing a block of data in a TAR archive */
struct tar_block {
    uint8_t data[TAR_BLOCK_SIZE];
};

/* A TAR element can be a header or a data block */
struct tar_element {
    struct tar_block block;  // 512 bytes of data (header or data)
    int is_header;           // 1 if it's a header, 0 if it's a data block
};

/* Structure representing a TAR archive */
struct tar_archive {
    struct tar_element *elements;  // Dynamically allocated array of elements
    size_t element_count;          // Number of elements in the archive
    size_t capacity;               // Actual capacity of the elements array
};

/* Function to initialize a TAR archive */
void init_tar_archive(struct tar_archive *archive);

/* Function to add a TAR header to the archive */
void add_tar_header(struct tar_archive *archive, const struct tar_header *header);

/* Function to add a block of data to the archive */
void add_tar_data_block(struct tar_archive *archive, const uint8_t *data, size_t size);

/* Function to finalize the archive by adding two empty blocks */
void finalize_tar_archive(struct tar_archive *archive);

/* Function to free the memory used by a TAR archive */
void free_tar_archive(struct tar_archive *archive);

#endif /* TAR_ARCHIVE_H */
