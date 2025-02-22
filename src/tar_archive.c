#include "../include/tar_archive.h"
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10  // Initial capacity of the archive

/* Function to expand the capacity of the archive */
static void expand_tar_archive(struct tar_archive *archive) {
    if (archive->element_count >= archive->capacity) {
        archive->capacity = archive->capacity ? archive->capacity * 2 : INITIAL_CAPACITY;
        archive->elements = realloc(archive->elements, archive->capacity * sizeof(struct tar_element));
        if (!archive->elements) {
            fprintf(stderr, "Memory allocation failed while expanding TAR archive.\n");
            exit(EXIT_FAILURE);
        }
    }
}

/* Function to initialize a TAR archive */
void init_tar_archive(struct tar_archive *archive) {
    archive->elements = malloc(INITIAL_CAPACITY * sizeof(struct tar_element));
    if (!archive->elements) {
        fprintf(stderr, "Memory allocation failed while initializing TAR archive.\n");
        exit(EXIT_FAILURE);
    }
    archive->element_count = 0;
    archive->capacity = INITIAL_CAPACITY;
}

/* Function to add a TAR header to the archive */
void add_tar_header(struct tar_archive *archive, const struct tar_header *header) {
    expand_tar_archive(archive);
    struct tar_element *element = &archive->elements[archive->element_count++];
    memset(element->block.data, 0, TAR_BLOCK_SIZE); // Fill with zeros by precaution
    memcpy(element->block.data, header, sizeof(struct tar_header)); // Copy the header to the block
    element->is_header = 1;
}

/* Function to add a block of data to the archive */
void add_tar_data_block(struct tar_archive *archive, const uint8_t *data, size_t size) {
    expand_tar_archive(archive);
    struct tar_element *element = &archive->elements[archive->element_count++];
    memset(element->block.data, 0, TAR_BLOCK_SIZE); // Fill with zeros by precaution
    memcpy(element->block.data, data, size > TAR_BLOCK_SIZE ? TAR_BLOCK_SIZE : size);
    element->is_header = 0;
}

/* Function to finalize the archive by adding two empty blocks */
void finalize_tar_archive(struct tar_archive *archive) {
    uint8_t zero_block[TAR_BLOCK_SIZE] = {0};
    for (int i = 0; i < 2; i++) {
        add_tar_data_block(archive, zero_block, TAR_BLOCK_SIZE);
    }
}

/* Function to free the memory used by a TAR archive */
void free_tar_archive(struct tar_archive *archive) {
    if (archive->elements) {
        free(archive->elements);
    }
    archive->elements = NULL;
    archive->element_count = 0;
    archive->capacity = 0;
}
