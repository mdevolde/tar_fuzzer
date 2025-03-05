#ifndef TAR_ARCHIVE_H
#define TAR_ARCHIVE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tar_header.h"

#define TAR_BLOCK_SIZE 512

/* Stuct representing a block of data in a TAR archive */
typedef struct {
    uint8_t data[TAR_BLOCK_SIZE];
} tar_block;

/* A TAR element can be a header or a data block */
typedef struct {
    tar_block block;  // 512 bytes of data (header or data)
    bool is_header;   // True if the block is a header, false if it is a data block
} tar_element;

/* Structure representing a TAR archive */
typedef struct {
    tar_element *elements;  // Dynamically allocated array of elements
    size_t element_count;   // Number of elements in the archive
    size_t capacity;        // Actual capacity of the elements array
} tar_archive;

/** Function to initialize a TAR archive
 * 
 * @param archive The archive to init
 * @return void
 */
void init_tar_archive(tar_archive *archive);

/** Function to add a TAR header to the archive
 * 
 * @param archive The archive to add the header
 * @param header The header to add
 * @return void
 */
void add_tar_header(tar_archive *archive, const tar_header *header);

/** Function to add a block of data to the archive
 * 
 * @param archive The archive to add the data block
 * @param data The data to add
 * @param size The size of the data
 * @return void
 */
void add_tar_data_block(tar_archive *archive, const uint8_t *data, size_t size);

/** Function to finalize a TAR archive with two empty blocks
 * 
 * @param archive The archive to finalize
 * @return void
 */
void finalize_tar_archive(tar_archive *archive);

/** Function to write a TAR archive to a file
 * 
 * @param archive The archive to write
 * @param filename The name of the file
 * @return true if the archive was written successfully, false otherwise
 */
bool write_tar_archive(const tar_archive *archive, const char *filename);

/** Function to free the memory used by a TAR archive
 * 
 * @param archive The archive to free
 * @return void
 */
void free_tar_archive(tar_archive *archive);

#endif /* TAR_ARCHIVE_H */
