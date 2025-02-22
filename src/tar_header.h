#ifndef TAR_HEADER_H
#define TAR_HEADER_H

#include <stdint.h>

#define TAR_BLOCK_SIZE 512
#define TAR_NAME_SIZE 100
#define TAR_PREFIX_SIZE 155

/* Structure of header TAR (format POSIX 1003.1-1990) */
typedef struct  {
    char name[TAR_NAME_SIZE];      /* Name of the file (0-99) */
    char mode[8];                  /* Permissions of the file (100-107) */
    char uid[8];                   /* UID owner (108-115) */
    char gid[8];                   /* GID owner (116-123) */
    char size[12];                  /* Size of the file in octal (124-135) */
    char mtime[12];                 /* Date of last modification in octal (136-147) */
    char chksum[8];                 /* Checksum for header (148-155) */
    char typeflag;                   /* Type of file (156) */
    char linkname[TAR_NAME_SIZE];    /* Name of the linked file (157-256) */
    char magic[6];                   /* Magic number (257-262) */
    char version[2];                 /* Version of the TAR format (263-264) */
    char uname[32];                  /* Name of the user (265-296) */
    char gname[32];                  /* Name of the group (297-328) */
    char devmajor[8];                /* Number major of the device (329-336) */
    char devminor[8];                /* Number minor du device (337-344) */
    char prefix[TAR_PREFIX_SIZE];    /* Prefix of the file name (345-500) */
    char padding[12];                /* Padding (501-512) */
} tar_header;

/* Function to initialize the header of a TAR file */
void init_tar_header(tar_header *header, const char *filename, uint32_t file_size);

/* Function to calculate the checksum of a TAR header */
void calculate_tar_checksum(tar_header *header);

#endif /* TAR_HEADER_H */
