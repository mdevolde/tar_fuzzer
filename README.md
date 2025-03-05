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

Don't forget that the extractor has to be executable and with linux line endings. If you are not sure, you can run the following commands:

```bash
chmod +x ./extractor
sed -i 's/\r$//' fichier.txt
```

**Warning**: The fuzzer will delete all `.tar` files in the current directory.

## Testing

To test the fuzzer, you can run the following command:

```bash
./fuzzer_test
```

It will test the fuzzer with a fake extractor that will crash in all cases to ensure that all fuzzer functionalities are working correctly.

**Warning**: The fuzzer will delete all `.tar` files in the current directory.