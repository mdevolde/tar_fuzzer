#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tar_archive.h"
#include "../tar_header.h"
#include "attack_linkname_invalid.h"

void attack_linkname_invalid(const char *output_filename, int index) {
    const char *link_variations[] = {
        "/etc/passwd",
        "../etc/shadow",
        "this_is_a_very_long_symlink_name_that_may_break_parsers",
        "\xFF\xFF\xFF\xFF",
        "link_with_null_byte\0hidden",
        "trailing_space "
    };

    int num_variants = sizeof(link_variations) / sizeof(link_variations[0]);
    const char *corrupt_linkname = link_variations[index % num_variants];

    tar_archive archive;
    init_tar_archive(&archive);

    tar_header header;
    init_tar_header(&header, "linkname_test.txt", 1024);
    
    snprintf(header.linkname, sizeof(header.linkname), "%s", corrupt_linkname);

    add_tar_header(&archive, &header);
    finalize_tar_archive(&archive);
    write_tar_archive(&archive, output_filename);
    free_tar_archive(&archive);
}
