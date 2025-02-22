#include "test_tar_header.h"
#include "test_tar_archive.h"
#include "test_tar_archive_longfile.h"


int main() {
    test_tar_header();
    test_tar_archive();
    test_tar_archive_longfile();
    return 0;
}
