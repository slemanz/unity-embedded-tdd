# Anatomy of a TDD Project

Adopting TDD changes the structure of an embedded project. The most important
principle is simple but non-negotiable: **test code and production code must be
kept separate.** Everything that follows is a consequence of honoring that
separation.

## The Standard IDE Project Structure

A typical IDE project, whether in STM32CubeIDE, Keil MDK, or IAR Embedded
Workbench, follows a familiar layout:

- **Core** — the main application logic, including `main.c`.
- **Drivers** — the low-level drivers, such as the CMSIS files and the vendor HAL
  drivers.
- **Generated folders and files** — build artifacts such as the `.elf` file, plus a
  **Debug** folder, all produced automatically when the project is built.

## TDD Additions

On top of the standard structure, TDD introduces its own dedicated area. A new
folder, conventionally named **TDD**, holds everything related to testing:

- **test** — the test runner files and the test cases themselves.
- **unity** — the source code for the Unity test framework. It is a remarkably
  small set of files that simply needs to be included.
- **cmock** — the CMock framework together with its generated mocks.

Keeping all of this under a single top-level folder makes the boundary between
test and production code explicit at a glance:

```
MyProject/
├── Core/                 # Application logic
│   ├── Inc/
│   └── Src/
│       └── main.c
├── Drivers/              # CMSIS and vendor HAL drivers
│   ├── CMSIS/
│   └── STM32xx_HAL_Driver/
├── Debug/                # Build artifacts (generated)
│   └── MyProject.elf
└── TDD/                  # TDD additions (excluded from build)
    ├── test/             # Test runners and test cases
    ├── unity/            # Unity test framework source
    └── cmock/            # CMock framework and generated mocks
```

## Excluding the TDD Folder from the Build

Critically, **the TDD folder must not be compiled into the final firmware.** It is
excluded from the production build for two reasons:

- **It can introduce build errors.** Generic C files written for a host test runner
  may contain elements the embedded compiler cannot render as part of the target
  image.
- **It does not belong in production.** Test code serves no purpose on the device
  and would only bloat the final binary.

Most IDEs provide a way to exclude code from the build. In STM32CubeIDE, for
example, an entire folder or individual files can be marked as *excluded from
build*.

## A Simpler Layout

The structure above uses subfolders (`test`, `unity`, `cmock`) inside the TDD
folder. A more minimal variant skips the subfolders entirely: a single **TDD**
folder holds all the files directly.

```
MyProject/
├── Core/
├── Drivers/
└── TDD/                  # All test files in one flat folder
    ├── test_main.c
    ├── unity.c
    ├── unity.h
    └── cmock.c
```

Either layout is valid; the choice depends on how much separation the project
needs.

## The Two Key Tools

Performing TDD in C relies on two frameworks that are used extensively throughout
this repository: **Unity** and **CMock**.

### Unity — The Test Runner and Referee

Unity is the test runner and the referee. It lets you write test functions and
provides a rich library of assertions to check whether the code produced the
expected result, delivering a final verdict as a simple **pass** or **fail**.

For example, the following assertion checks that the value returned by
`get_value()` equals `5`:

```c
TEST_ASSERT_EQUAL_UINT8(5, get_value());
```

Here `5` is the expected value and `get_value()` is the code under test. If the
function returns `5`, the assertion passes; otherwise it fails.

### CMock — The Stunt Double

CMock is the stunt double for the code. It reads the project's header files and
automatically generates fake versions of those modules. This is what makes it
possible to test a module that talks to a hardware driver **without needing the
actual hardware**, allowing the logic to be verified in complete isolation.