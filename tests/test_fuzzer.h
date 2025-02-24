#ifndef TEST_FUZZER_H
#define TEST_FUZZER_H

/**
 * Verify if a file exists.
 * @param filename The name of the file to check.
 * @return 1 if the file exists, 0 otherwise.
 */
int file_exists(const char *filename);

/**
 * Create a mock extractor to test the fuzzer.
 * @return void
 */
void create_mock_extractor();

/**
 * Test the fuzzer.
 * @return void
 */
void test_fuzzer();

#endif /* TEST_FUZZER_H */
