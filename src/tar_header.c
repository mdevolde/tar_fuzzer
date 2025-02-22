#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "tar_header.h"

uint32_t calculate_tar_checksum(const tar_header *header) {
    uint32_t sum = 0;
    tar_header header_clone = *header;
    
    memset(header_clone.chksum, ' ', sizeof(header_clone.chksum));

    // Sum of all bytes in the header
    unsigned char *p = (unsigned char *)&header_clone;
    for (size_t i = 0; i < sizeof header_clone; i++) {
        sum += p[i];
    }
    
    return sum;
}


void init_tar_header(tar_header *header, const char *filename, uint32_t file_size) {
    memset(header, 0, sizeof(tar_header));

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
    snprintf(header->chksum, sizeof(header->chksum), "%07o", calculate_tar_checksum(header));
}
