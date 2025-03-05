# Fuzzer Project

This project provides a fuzzing script designed to test the robustness of tar extractors. It generates deterministic inputs and executes them with the target script. The extractor has to send on the stdout `*** The program has crashed ***` in case of a crash. The fuzzer will then report the crash and the input that caused it.

## Installation

To install the fuzzer:

- Clone the repository
- Run the following command in the root directory of the project:
```bash
make
```

It will generate a `fuzzer` executable and a `fuzzer_test` executable.

## Usage

To use the fuzzer, you need to provide a target script that will be executed with the generated inputs like this:

```bash
./fuzzer ./extractor
```

**Warning**: The fuzzer will delete all `.tar` files in the current directory and delete all files in the current directory (except Makefile, README.md, .c files, .h files and files starting with `extractor`)  before starting the fuzzing process. So make sure that your extractor starts with `extractor` and that you don't have any important files in the current directory.