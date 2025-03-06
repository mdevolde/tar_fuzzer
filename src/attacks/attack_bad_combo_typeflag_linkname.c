#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "../header_fields.h"
#include "attack_bad_combo_typeflag_linkname.h"

bool attack_bad_combo_typeflag_linkname(const char *output_filename, uint8_t index) {
    bool is_header_tested = true;
    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "invalid_typeflag.txt", 1024);

    switch (index)
    {
    case 0: // Typeflag '5' (repertory) with linkname
        header.typeflag = '5';
        snprintf(header.size, sizeof(header.size), "%011o", 1024);
        break;
    case 1: // Typeflag '0' (regular file) with linkname
        header.typeflag = '0';
        snprintf(header.linkname, sizeof(header.linkname), "fake_link");
        break;
    case 2: // Typeflag '1' (hard link) with an empty linkname
        header.typeflag = '1';
        memset(header.linkname, 0, sizeof(header.linkname));
        break;
    case 3: // Typeflag '2' (symbolic link) with an empty linkname
        header.typeflag = '2';
        memset(header.linkname, 0, sizeof(header.linkname));
        break;
    case 4: // Typeflag '3' (character special) with linkname (doesn't make sense)
        header.typeflag = '3';
        snprintf(header.linkname, sizeof(header.linkname), "device_name");
        break;
    case 5: // Typeflag '4' (block special) with linkname (doesn't make sense)
        header.typeflag = '4';
        snprintf(header.linkname, sizeof(header.linkname), "block_device");
        break;
    case 6: // Typeflag '6' (FIFO) with linkname
        header.typeflag = '6';
        snprintf(header.linkname, sizeof(header.linkname), "pipe_fifo");
        break;
    case 7: // Typeflag invalid (':') with an empty linkname
        header.typeflag = ':';
        memset(header.linkname, 0, sizeof(header.linkname));
        break;
    case 8: // Typeflag invalid ('9') with an invalid linkname
        header.typeflag = '9';
        snprintf(header.linkname, sizeof(header.linkname), "invalid_typeflag");
        break;
    default:
        is_header_tested = false;
        break;
    }

    edit_tar_header_chksum(&header, calculate_tar_checksum(&header));

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);

    return is_header_tested;
}

char *combo_from_index(uint8_t index) {
    switch (index)
    {
    case 0:
        return "REPERTORY_LINKNAME";
    case 1:
        return "REGFILE_LINKNAME";
    case 2:
        return "HARDLINK_EMPTY";
    case 3:
        return "SYMLINK_EMPTY";
    case 4:
        return "CHARSPECIAL_LINKNAME";
    case 5:
        return "BLOCKSPECIAL_LINKNAME";
    case 6:
        return "FIFO_LINKNAME";
    case 7:
        return "INVALID_EMPTY";
    case 8:
        return "INVALID_LINKNAME";
    default:
        return "UNKNOWN";
    }
}
