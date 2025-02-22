#include <stdio.h>
#include <string.h>
#include "test_tar_archive.h"
#include "tar_archive.h"

/** Function to print the content of a TAR archive
 * @param archive The archive to print
 * @return void
 */
void print_tar_archive(const tar_archive *archive) {
    for (size_t i = 0; i < archive->element_count; i++) {
        printf("Element %zu (%s):\n", i, archive->elements[i].is_header ? "Header" : "Data");
        for (size_t j = 0; j < TAR_BLOCK_SIZE; j++) {
            printf("%02x ", archive->elements[i].block.data[j]);
            if ((j + 1) % 16 == 0) {
                printf("\n");
            }
        }
        printf("\n-----------------------------------\n");
    }
}

/* Function to test the TAR archive creation */
void test_tar_archive() {
    // 1. Init the TAR archive
    tar_archive archive;
    init_tar_archive(&archive);

    // 2. Create a TAR header for a file named "testfile.txt" with a size of 12 bytes
    tar_header header = {0}; 

    // Fill the header fields
    edit_tar_header_name(&header, "testfile.txt");
    edit_tar_header_mode(&header, 0644);        // Permissions in octal
    edit_tar_header_uid(&header, 1000);         // UID
    edit_tar_header_gid(&header, 1000);         // GID
    edit_tar_header_size(&header, 12);          // Size of the file in octal (12 bytes)
    edit_tar_header_mtime(&header, 1672531200); // Date (epoch time) of the file
    edit_tar_header_typeflag(&header, '0');     // Regular file
    edit_tar_header_magic(&header, "ustar");    // Format POSIX
    edit_tar_header_version(&header, "00");
    edit_tar_header_uname(&header, "user");
    edit_tar_header_gname(&header, "group");
    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    // 3. Add the header to the archive
    add_tar_header(&archive, &header);

    // 4. Add the content of the file
    const char *content = "Hello World\n";
    add_tar_data_block(&archive, (const uint8_t *)content, strlen(content));

    // 5. Finalize the archive (add the end blocks)
    finalize_tar_archive(&archive);

    // 6. Print the content of the archive
    print_tar_archive(&archive);

    // 7. Write the archive to a file
    FILE *file = fopen("test_archive.tar", "wb");
    if (file) {

        tar_element *elements = archive.elements;
        for (size_t i = 0; i < archive.element_count; i++) {
            fwrite(&elements[i].block, 1, sizeof(tar_block), file);
        }
        fclose(file);
        printf("The archive has been written to test_archive.tar\n");
    } else {
        perror("Error opening file");
    }

    // 8. Free the memory
    free_tar_archive(&archive);
}
