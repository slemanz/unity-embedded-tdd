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
