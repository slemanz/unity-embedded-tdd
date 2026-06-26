# TDD Template

A ready-to-use skeleton for starting a new Unity-based TDD example. Copy this
entire folder, replace the example module with your own production code, and start
writing tests.

## Structure

```
template/
├── Makefile          # Builds and runs the tests
├── src/              # Production code under test
│   ├── example.c
│   └── example.h
├── tests/            # Test cases and the test runner
│   ├── example_test.c
│   └── AllTestRunner.c
└── unity/            # Unity + CMock framework (vendored, with licenses)
```

## Running the Tests

```sh
make        # compile and run the test suite
make clean  # remove build artifacts
```

A successful run ends with `OK`; any failure prints the file, line, and reason.

## Adapting It to Your Project

1. Replace `src/example.c` and `src/example.h` with your own module(s).
2. Rename `tests/example_test.c` and write your `TEST_GROUP` / `TEST` cases.
3. Register the new group in `tests/AllTestRunner.c` with `RUN_TEST_GROUP(...)`.
4. Update the `OBJS` and `TEST_OBJS` lists in the `Makefile` to match your files.

The `unity/` folder is vendored as-is and rarely needs to change.
