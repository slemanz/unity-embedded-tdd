# Unity Assertions

This module is a tour through Unity's assertion vocabulary: the macros you use
inside a test to state what you expect and let the framework decide whether the
code agrees. Before exploring them, it helps to know that Unity offers two styles
of writing and running tests: **unity** and **unity_fixture**.

## The Core Framework

The core framework lives in `unity.c` and `unity.h`. This is the plain, minimal
style. You write free functions for your tests, register each one with `RUN_TEST`,
and wrap the whole batch between `UNITY_BEGIN` and `UNITY_END`. You also define the
two lifecycle hooks Unity calls around every test, `setUp` and `tearDown`,
yourself:

```c
void setUp(void)    { /* runs before each test */ }
void tearDown(void) { /* runs after each test  */ }

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_something);
    return UNITY_END();
}
```

## The Fixture Extension

The fixture extension lives in `unity_fixture.c` and `unity_fixture.h`. It adds a
higher-level layer on top of the core for organizing tests into named groups.
Instead of free functions and `RUN_TEST`, you write `TEST_GROUP`, `TEST_SETUP`,
`TEST_TEAR_DOWN`, and `TEST` blocks, then drive them with `RUN_TEST_GROUP` and
`RUN_TEST_CASE`. The fixture style already provides its own `setUp` and
`tearDown`, so you do not declare them.

## Which One Should You Use?

For small, focused test files like the ones in this module, the core style is the
simpler choice and keeps the runner readable. Reach for the fixture extension when
a suite grows large enough that grouping related tests, with shared setup and
teardown per group, pays for the extra ceremony. Either way, the assertion macros
behave identically. The only thing that changes is how the tests are organized and
run.

## The Assertions Covered

The practical examples live in
[`tests/test_unity_assertions.c`](tests/test_unity_assertions.c). The file walks
through Unity's assertion vocabulary one group at a time. Each group has a passing
test that always runs, and a matching failing test compiled in only when you build
with `-DDEMO_ENABLE_FAILS=1` (see the `fail` rule in the Makefile). The groups are:

**Boolean and pointer checks.** The starting point: `TEST_ASSERT` and its readable
forms `TEST_ASSERT_TRUE`, `TEST_ASSERT_FALSE`, and `TEST_ASSERT_UNLESS` (an alias
for asserting false), plus `TEST_ASSERT_NULL` and `TEST_ASSERT_NOT_NULL` for
checking pointers.

**Integer equality.** `TEST_ASSERT_EQUAL` and its alias `TEST_ASSERT_EQUAL_INT`,
together with the width-specific variants for signed and unsigned values:
`INT8`/`INT16`/`INT32` and `UINT`/`UINT8`/`UINT16`/`UINT32`. The width matters
because it tells Unity how to interpret and report the values.

**Hexadecimal equality.** The same idea as integer equality, but `EQUAL_HEX8`,
`EQUAL_HEX16`, and `EQUAL_HEX32` print mismatches in hex, which reads better when
you are working with registers or byte patterns.

**Bitmask and bit-level checks.** `TEST_ASSERT_BITS` compares only the bits picked
out by a mask, while `TEST_ASSERT_BITS_HIGH` and `TEST_ASSERT_BITS_LOW` assert
groups of bits, and `TEST_ASSERT_BIT_HIGH` and `TEST_ASSERT_BIT_LOW` target a
single bit by position.

**Relational comparisons.** `TEST_ASSERT_GREATER_THAN` and `TEST_ASSERT_LESS_THAN`
compare an actual value against a threshold rather than checking for equality.

**Range checks within a delta.** `TEST_ASSERT_INT_WITHIN` and
`TEST_ASSERT_UINT_WITHIN` pass when the actual value sits within a given tolerance
of the expected one, which is handy when an exact match is too strict.

**Pointers, strings, and raw memory.** `TEST_ASSERT_EQUAL_PTR` compares addresses,
`TEST_ASSERT_EQUAL_STRING` compares C strings and `TEST_ASSERT_EQUAL_STRING_LEN`
compares only a leading slice of them, and `TEST_ASSERT_EQUAL_MEMORY` compares an
arbitrary block byte by byte.

**Array equality.** The `_ARRAY` family checks two arrays element by element:
`EQUAL_INT16_ARRAY`, `EQUAL_UINT8_ARRAY`, `EQUAL_STRING_ARRAY`, `EQUAL_PTR_ARRAY`,
and `EQUAL_MEMORY_ARRAY` (which takes an element size and a count).

**Arrays against a single value.** The `EACH_EQUAL` family asserts that every
element of an array matches one expected value: `EACH_EQUAL_UINT16`,
`EACH_EQUAL_STRING`, and `EACH_EQUAL_MEMORY`.

**Floating point.** Because exact float equality is fragile, Unity offers
`TEST_ASSERT_EQUAL_FLOAT` and the tolerance-based `TEST_ASSERT_FLOAT_WITHIN`,
the array form `TEST_ASSERT_EACH_EQUAL_FLOAT`, and a set of predicates for special
values: `FLOAT_IS_INF`, `FLOAT_IS_NAN`, `FLOAT_IS_DETERMINATE`, and their negated
counterparts `FLOAT_IS_NOT_INF`, `FLOAT_IS_NOT_NEG_INF`, and `FLOAT_IS_NOT_NAN`.

**Flow control helpers.** Not assertions in the strict sense, but they steer the
outcome of a test directly: `TEST_PASS_MESSAGE` ends the test as passed,
`TEST_FAIL_MESSAGE` forces a failure with a note, and `TEST_IGNORE_MESSAGE` marks
the test as skipped.

## Running the Examples

The Makefile builds and runs everything for you. From this directory:

```sh
make        # build the passing suite and run it
make fail   # also compile the failing tests (-DDEMO_ENABLE_FAILS=1) and run them
make clean  # remove the build artifacts
```

`make` is the everyday command: it compiles the passing tests into
`build/run_tests` and runs them, so a clean run means every assertion behaved as
expected. `make fail` is there to show the other side, enabling the deliberately
failing tests so you can see what Unity prints when an assertion does not hold. It
ends with a non-zero status on purpose, which is the expected outcome for that
demo.
