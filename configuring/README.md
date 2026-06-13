# Configuring and Building Unity

Unity is not a heavy dependency that gets installed system-wide; it is a small set
of C source files that are **vendored** directly into the project and compiled
alongside the code under test. Understanding how those files come together in a
build is the key to configuring TDD for any embedded project.

A complete, working skeleton lives in [`../template`](../template/README.md). This
section explains how that skeleton is wired together.

## What Gets Compiled

A Unity test build links together three distinct groups of object files:

- **Production code** — the modules under test, taken from `src/` (for example,
  `example.c`).
- **Test code** — the test cases and the runner from `tests/` (`example_test.c`
  and `AllTestRunner.c`).
- **The Unity framework** — `unity.c` and `unity_fixture.c` from the vendored
  `unity/` folder.

Each `.c` file is compiled into an object file under `build/`, and those objects
are linked into a single executable, `run_tests`, which is then run directly on
the host machine.

## The Folder Layout

```
template/
├── Makefile
├── src/              # Production code under test
├── tests/            # Test cases + AllTestRunner.c
└── unity/            # Unity + CMock source (vendored)
```

Keeping `unity/` self-contained means the framework travels with the project: a
fresh clone builds and tests without any external setup.

## The Makefile, Step by Step

The build is driven by a deliberately simple Makefile. A few variables declare
where things live and which files to compile:

```make
CC = gcc
CFLAGS = -c -Wall -Wextra -std=gnu99 -g -O0

BUILD_DIR = build
SRC_DIR   = src
TEST_DIR  = tests
UNITY_DIR = unity

INCLUDES += -I $(UNITY_DIR)
INCLUDES += -I $(SRC_DIR)
INCLUDES += -I $(TEST_DIR)
```

The `-I` flags let the compiler find the headers: the Unity headers, the
production headers, and the test headers.

The source files are grouped so the lists are easy to extend as the project grows:

```make
OBJS      += $(BUILD_DIR)/example.o          # production code

TEST_OBJS += $(BUILD_DIR)/example_test.o     # test cases
TEST_OBJS += $(BUILD_DIR)/AllTestRunner.o    # the runner

UNITY     += $(BUILD_DIR)/unity.o            # framework
UNITY     += $(BUILD_DIR)/unity_fixture.o
```

A pattern rule per directory tells `make` how to turn any `.c` file into an object
file inside `build/`:

```make
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
```

Finally, the `run_tests` target links every object file together and immediately
executes the resulting binary, so a single `make` both builds and runs the suite:

```make
$(BUILD_DIR)/run_tests: $(TEST_OBJS) $(OBJS) $(UNITY)
	$(CC) -o $@ $^
	./$@
```

## Running It

```sh
make        # compile everything and run the tests
make clean  # delete the build artifacts
```

A passing run reports a concise summary:

```
Unity test run 1 of 1
..

-----------------------
2 Tests 0 Failures 0 Ignored
OK
```

Any failing assertion replaces `OK` with the exact file, line number, and reason,
making it immediate to locate the problem.

## The Test Runner

Unity does not discover tests automatically; they are wired in explicitly. Each
module groups its cases into a `TEST_GROUP_RUNNER`, and a single top-level runner
calls every group through `UnityMain`:

```c
#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Example);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
```

Adding a new module to the suite is a three-step change: write its tests, register
its group here with `RUN_TEST_GROUP(...)`, and add its object files to the
`Makefile` lists.

## Licensing

The vendored framework keeps its original license files, `LICENSE_unity.txt` and
`LICENSE_cmock.txt`, inside the `unity/` folder. Both Unity and CMock are released
under the permissive MIT license, so they can be shipped inside a project as long
as those notices are preserved.
