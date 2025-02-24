#include "test_tar_header.h"
#include "test_tar_archive.h"
#include "test_tar_archive_longfile.h"
#include "test_fuzzer.h"

int main() {
    test_tar_header();
    test_tar_archive();
    test_tar_archive_longfile();
    test_fuzzer();
    return 0;
}
