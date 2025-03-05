#ifndef TAR_HEADER_H
#define TAR_HEADER_H

#include <stdint.h>
#include <time.h>

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

/** Function to calculate the checksum of a TAR header
 * 
 * @param header The header to calculate the checksum
 * @return The checksum of the header
 *  */
uint32_t calculate_tar_checksum(const tar_header *header);

/** Function to edit the name of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param filename The new name of the file
 * @return void   
 * */
void edit_tar_header_name(tar_header *header, const char *filename);

/** Function to edit the mode of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param mode The new mode of the file
 * @return void   
 * */
void edit_tar_header_mode(tar_header *header, const uint32_t mode);

/** Function to edit the UID of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param uid The new UID of the file
 * @return void   
 * */
void edit_tar_header_uid(tar_header *header, const uint32_t uid);

/** Function to edit the GID of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param gid The new GID of the file
 * @return void   
 * */
void edit_tar_header_gid(tar_header *header, const uint32_t gid);

/** Function to edit the size of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param size The new size of the file
 * @return void   
 * */
void edit_tar_header_size(tar_header *header, const uint32_t size);

/** Function to edit the mtime of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param mtime The new mtime of the file
 * @return void   
 * */
void edit_tar_header_mtime(tar_header *header, const time_t mtime);

/** Function to edit the typeflag of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param typeflag The new type of the file
 * @return void   
 * */
void edit_tar_header_typeflag(tar_header *header, char typeflag);

/** Function to edit the magic of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param magic The new magic number
 * @return void   
 * */
void edit_tar_header_magic(tar_header *header, const char *magic);

/** Function to edit the version of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param version The new version of the TAR format
 * @return void   
 * */
void edit_tar_header_version(tar_header *header, const char *version);

/** Function to edit the uname of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param uname The new name of the user
 * @return void   
 * */
void edit_tar_header_uname(tar_header *header, const char *uname);

/** Function to edit the gname of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param g
 * @return void   
 * */
void edit_tar_header_gname(tar_header *header, const char *gname);

/** Function to edit the checksum of a TAR header in a legacy way
 * 
 * @param header The header to edit
 * @param chksum The new checksum of the header
 * @return void   
 * */
void edit_tar_header_chksum(tar_header *header, const uint32_t chksum);

/** Function to initialize a TAR header
 * 
 * @param header The header to init
 * @param filename The name of the file
 * @param file_size The size of the file
 * @return void   
 * */
void init_tar_header(tar_header *header, const char *filename, uint32_t file_size);

#endif /* TAR_HEADER_H */
