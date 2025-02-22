#ifndef TEST_TAR_ARCHIVE_H
#define TEST_TAR_ARCHIVE_H

#include "tar_archive.h"

/** Function to print the content of a TAR archive
 * @param archive The archive to print
 * @return void
 */
void print_tar_archive(const tar_archive *archive);

/* Function to test the TAR archive creation */
void test_tar_archive();

#endif
