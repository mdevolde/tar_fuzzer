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


void edit_tar_header_name(tar_header *header, const char *filename) {
    snprintf(header->name, TAR_NAME_SIZE, "%s", filename);
}


void edit_tar_header_mode(tar_header *header, const uint32_t mode) {
    snprintf(header->mode, sizeof(header->mode), "%07o", mode);
}


void edit_tar_header_uid(tar_header *header, const uint32_t uid) {
    snprintf(header->uid, sizeof(header->uid), "%07o", uid);
}


void edit_tar_header_gid(tar_header *header, const uint32_t gid) {
    snprintf(header->gid, sizeof(header->gid), "%07o", gid);
}


void edit_tar_header_size(tar_header *header, const uint32_t size) {
    snprintf(header->size, sizeof(header->size), "%011o", size);
}


void edit_tar_header_mtime(tar_header *header, const time_t mtime) {
    snprintf(header->mtime, sizeof(header->mtime), "%011o", (unsigned int)mtime);
}


void edit_tar_header_typeflag(tar_header *header, const char typeflag) {
    header->typeflag = typeflag;
}


void edit_tar_header_magic(tar_header *header, const char *magic) {
    snprintf(header->magic, sizeof(header->magic), "%s", magic);
}


void edit_tar_header_version(tar_header *header, const char *version) {
    memcpy(header->version, version, 2);
}


void edit_tar_header_uname(tar_header *header, const char *uname) {
    snprintf(header->uname, sizeof(header->uname), "%s", uname);
}


void edit_tar_header_gname(tar_header *header, const char *gname) {
    snprintf(header->gname, sizeof(header->gname), "%s", gname);
}


void edit_tar_header_chksum(tar_header *header, const uint32_t checksum) {
    snprintf(header->chksum, sizeof(header->chksum), "%07o", checksum);
}


void init_tar_header(tar_header *header, const char *filename, uint32_t file_size) {
    memset(header, 0, sizeof(tar_header));
    edit_tar_header_name(header, filename);
    edit_tar_header_mode(header, 0644);
    edit_tar_header_uid(header, 1000);
    edit_tar_header_gid(header, 1000);
    edit_tar_header_size(header, file_size);
    edit_tar_header_mtime(header, time(NULL));
    edit_tar_header_typeflag(header, '0');
    edit_tar_header_magic(header, "ustar");
    edit_tar_header_version(header, "00");
    edit_tar_header_uname(header, "user");
    edit_tar_header_gname(header, "group");
    edit_tar_header_chksum(header, calculate_tar_checksum(header));
}
