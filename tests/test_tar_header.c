#include <stdio.h>
#include "../include/tar_header.h"

/** Function to print the content of a TAR header
 * @param header The header to print
 * @return void
 */
void print_tar_header(const struct tar_header *header) {
    printf("=== TAR HEADER TEST ===\n");
    printf("Name of file : %s\n", header->name);
    printf("Mode : %s\n", header->mode);
    printf("UID : %s\n", header->uid);
    printf("GID : %s\n", header->gid);
    printf("Taille : %s\n", header->size);
    printf("MTime : %s\n", header->mtime);
    printf("Checksum : %s\n", header->chksum);
    printf("Typeflag : %c\n", header->typeflag);
    printf("Magic : %s\n", header->magic);
    printf("Version : %.2s\n", header->version);
    printf("Uname : %s\n", header->uname);
    printf("Gname : %s\n", header->gname);
    printf("========================\n");
}

/** Main function
 * @return 0
 */
int main() {
    struct tar_header header;
    
    // Generate a header for a file named "testfile.txt" with a size of 1024 bytes
    init_tar_header(&header, "testfile.txt", 1024);

    // Print the header
    print_tar_header(&header);

    // Write the header to a file
    FILE *file = fopen("test_header.bin", "wb");
    if (file) {
        fwrite(&header, 1, sizeof(header), file);
        fclose(file);
        printf("The header has been written to test_header.bin\n");
    } else {
        perror("Error opening file");
    }

    return 0;
}
