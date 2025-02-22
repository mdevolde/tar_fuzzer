#include "../include/tar_header.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void init_tar_header(struct tar_header *header, const char *filename, uint32_t file_size) {
    memset(header, 0, sizeof(struct tar_header));

    snprintf(header->name, TAR_NAME_SIZE, "%s", filename);
    snprintf(header->mode, sizeof(header->mode), "%07o", 0644);
    snprintf(header->uid, sizeof(header->uid), "%07o", 1000);
    snprintf(header->gid, sizeof(header->gid), "%07o", 1000);
    snprintf(header->size, sizeof(header->size), "%011o", file_size);
    snprintf(header->mtime, sizeof(header->mtime), "%011o", (unsigned int)time(NULL));
    header->typeflag = '0';
    snprintf(header->magic, sizeof(header->magic), "ustar");
    memcpy(header->version, "00", 2);
    memset(header->uname, 0, sizeof(header->uname));
    snprintf(header->uname, sizeof(header->uname), "user");
    snprintf(header->gname, sizeof(header->gname), "group");

    calculate_tar_checksum(header);
}

void calculate_tar_checksum(struct tar_header *header) {
    unsigned int sum = 0;
    memset(header->chksum, ' ', sizeof(header->chksum));

    // Sum of all bytes in the header
    unsigned char *p = (unsigned char *)header;
    for (size_t i = 0; i < TAR_BLOCK_SIZE; i++) {
        sum += p[i];
    }

    // Replace the checksum field with the calculated sum
    snprintf(header->chksum, sizeof(header->chksum), "%06o ", sum);
}
