#include <string.h>
#include <stdio.h>
#include "tar_archive.h"

#define INITIAL_CAPACITY 10  // Initial capacity of the archive


static void expand_tar_archive(tar_archive *archive) {
    if (archive->element_count >= archive->capacity) {
        archive->capacity = archive->capacity ? archive->capacity * 2 : INITIAL_CAPACITY;
        archive->elements = realloc(archive->elements, archive->capacity * sizeof(tar_element));
        if (!archive->elements) {
            fprintf(stderr, "Memory allocation failed while expanding TAR archive.\n");
            exit(EXIT_FAILURE);
        }
    }
}


void init_tar_archive(tar_archive *archive) {
    archive->elements = calloc(INITIAL_CAPACITY, sizeof(tar_element));
    if (!archive->elements) {
        fprintf(stderr, "Memory allocation failed while initializing TAR archive.\n");
        exit(EXIT_FAILURE);
    }
    archive->element_count = 0;
    archive->capacity = INITIAL_CAPACITY;
}


void add_tar_header(tar_archive *archive, const tar_header *header) {
    expand_tar_archive(archive);
    tar_element *element = &archive->elements[archive->element_count++];
    memset(element->block.data, 0, TAR_BLOCK_SIZE); // Fill the block with zeros
    memcpy(element->block.data, header, sizeof(tar_header)); // Copy the header to the block
    element->is_header = 1;
}


void add_tar_data_block(tar_archive *archive, const uint8_t *data, size_t size) {
    expand_tar_archive(archive);
    tar_element *element = &archive->elements[archive->element_count++];
    memset(element->block.data, 0, TAR_BLOCK_SIZE); // Fill the block with zeros
    memcpy(element->block.data, data, size > TAR_BLOCK_SIZE ? TAR_BLOCK_SIZE : size);
    element->is_header = 0;

    if (size > TAR_BLOCK_SIZE) {
        add_tar_data_block(archive, data + TAR_BLOCK_SIZE, size - TAR_BLOCK_SIZE);
    }
}


void finalize_tar_archive(tar_archive *archive) {
    uint8_t zero_block[TAR_BLOCK_SIZE] = {0};
    for (int i = 0; i < 2; i++) {
        add_tar_data_block(archive, zero_block, TAR_BLOCK_SIZE);
    }
}


bool write_tar_archive(const tar_archive *archive, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        tar_element *elements = archive->elements;
        for (size_t i = 0; i < archive->element_count; i++) {
            fwrite(&elements[i].block, 1, sizeof(tar_block), file);
        }
        fclose(file);
        return true;
    } else {
        return false;
    }
}


void free_tar_archive(tar_archive *archive) {
    if (archive->elements) {
        free(archive->elements);
    }
    archive->elements = NULL;
    archive->element_count = 0;
    archive->capacity = 0;
}
