# Unity Assertions

This module is a tour through Unity's assertion vocabulary: the macros you use
inside a test to state what you expect and let the framework decide whether the
code agrees. Before exploring them, though, it is worth clearing up a point of
confusion that trips up almost everyone the first time they build a Unity
project: the difference between **unity** and **unity_fixture**.

## Two Ways to Run a Test

Unity ships with two styles of writing and running tests, and they are not meant
to be mixed in the same runner. Knowing which one you are using tells you which
files to compile and link.

The **core framework** lives in `unity.c` and `unity.h`. This is the plain,
minimal style. You write free functions for your tests, register each one with
`RUN_TEST`, and wrap the whole batch between `UNITY_BEGIN` and `UNITY_END`. In
this style, *you* are responsible for defining the two lifecycle hooks Unity calls
around every test:

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

The **fixture extension** lives in `unity_fixture.c` and `unity_fixture.h`. It
adds a higher-level layer on top of the core for people who want their tests
organized into named groups. Instead of free functions and `RUN_TEST`, you write
`TEST_GROUP`, `TEST_SETUP`, `TEST_TEAR_DOWN`, and `TEST` blocks, then drive them
with `RUN_TEST_GROUP` and `RUN_TEST_CASE`. The fixture style brings its own
default `setUp` and `tearDown`, so you do **not** declare them yourself.

## Why You Cannot Link Both Blindly

Here is the catch that produces a confusing linker error. `unity_fixture.c`
already contains its own definitions:

```c
void setUp(void)    { /*does nothing*/ }
void tearDown(void) { /*does nothing*/ }
```

If you write tests in the plain style (defining `setUp` and `tearDown` yourself)
and *also* link `unity_fixture.o`, the linker sees the same symbol defined twice
and refuses to finish:

```
multiple definition of `setUp'; ... defined first here
```

The fix is not to silence the error but to decide which style you are using and
link accordingly. This module's tests use the **core style**, so the Makefile
links only `unity.o`:

```make
# Unity framework
UNITY += $(BUILD_DIR)/unity.o
```

If you ever switch to the fixture style, do the opposite: link `unity_fixture.o`
and remove your own `setUp`/`tearDown` definitions so they no longer collide with
the ones the extension provides.

## Which One Should You Use?

For small, focused test files like the ones in this module, the **core style** is
the simpler choice and keeps the runner readable. Reach for the **fixture
extension** when a suite grows large enough that grouping related tests, with
shared setup and teardown per group, starts to pay for the extra ceremony. Either
way, the assertion macros described below behave identically. The only thing that
changes is how the tests are organized and run.
