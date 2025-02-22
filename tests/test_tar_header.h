#ifndef TEST_TAR_HEADER_H
#define TEST_TAR_HEADER_H

#include "tar_header.h"

/** Function to print the content of a TAR header
 * @param header The header to print
 * @return void
 */
void print_tar_header(const tar_header *header);

/** Main function
 * @return 0
 */
int test_tar_header();

#endif
