# The Unity Framework

The previous module established the **why**: the professional and financial
reasons for building robust firmware. This module is about the **how**. It is
where the Red-Green-Refactor cycle stops being a theoretical concept and starts
becoming muscle memory.

The goal is to make the cycle so second nature that you begin to think in terms of
a single question: *what is my next failing test?* Everything that follows is
practice toward that habit.

## Red: Design Before You Implement

The cycle begins with a failing test, and it helps to treat this as the most
important design phase, not a formality you rush through before the real work.

Writing the test first forces you to become the **first user of your own code**.
Before any production code exists, you have to answer concrete questions:

- What should this function be called?
- What information does it need to receive?
- What should it give back?

In other words, you are designing the public interface, its name, its parameters,
and its return type, by deciding how you want to call it. You even get to ask the
most useful question of all: is this API actually pleasant to use? It is far
cheaper to answer that now than after the implementation is written.

Then you run the test and watch it fail. **This is not a mistake, it is a
victory.** A failing test proves you have correctly described a requirement the
system does not yet meet. It sounds counterintuitive, but it is the point: you
write just enough test code to trigger a compiler error or a red bar, and that red
bar is your clearly defined goal.

## Green: The Simplest Thing That Works

Once you have a failing test, you enter the green phase, and here the goal is
singular: move the bar from red to green as quickly as possible.

You do that by writing the simplest, most direct code imaginable. If the test
expects the number five, you are allowed to literally return five. That feels
wrong at first, and learning to be comfortable with it is part of the discipline.
It guarantees that your production code is driven only by the requirements the
tests actually specify.

We are not aiming for beautiful code at this stage, we are aiming for a working
system and a stable, passing state. That means you must **resist overengineering**.
Add no logic the test does not explicitly ask for: no future-proofing, no gold
plating. The only key action here is to write production code until the bar turns
from red to green, and no further.

## Refactor: Earn the Right to Improve

With a full suite of passing tests acting as a safety net, you have earned the
right to refactor. Now you put on your software architect hat.

You look at the simple code you just wrote and ask how it can be made better: more
readable, more efficient, more maintainable. Because the tests are green, you can
make these changes with complete confidence. If a refactor breaks something, a
test fails and you know instantly, while the mistake is still small and fresh in
your mind. This is the phase that turns a functional but messy codebase into a
genuinely professional one.

The key action at this stage is to improve the production code, the test code, or
both, running your tests after every small change.

## The Loop

Red defines the goal, green reaches it the fastest way possible, and refactor
makes the result something you would be proud to ship. Then the cycle begins again
with the next failing test. Repeat it enough times and it stops being a procedure
you follow and becomes the way you think.

## What Makes a Good Unit Test

The cycle is only as good as the tests you feed into it. A bad test can be worse
than no test at all: it gives you false confidence, or it turns into a brittle,
time-consuming maintenance burden. So before writing more tests, it is worth
defining what a good unit test actually looks like, so that the tests become
valuable assets to the project rather than liabilities.

A useful way to remember the qualities of a solid unit test is the acronym
**FIRST**.

**Fast**

A host-based test should run in the blink of an eye. When the whole suite finishes
in a moment, you run it constantly, and that tight feedback loop is what keeps the
Red-Green-Refactor cycle alive.

**Independent**

Each test should start from a clean slate, with no dependence on the order or the
side effects of any other test. This is exactly what `setup` and `teardown` are
for: they prepare fresh state before every case and clean it up afterward.

**Repeatable**

A test should give the same result every time it runs, regardless of the
environment. This is the core reason we reach for mocks: they remove the
unpredictability of physical hardware from the unit test, so the outcome depends
only on the logic under test.

**Self-Validating**

A test must decide its own outcome with no ambiguity. There is no middle ground and
no human left to interpret the result: the test either passes or it fails. Unity
handles this for us through its assertions.

**Timely**

Write the test first. This is the very definition of TDD, and it is what lets the
test drive the design instead of merely checking work that is already done.

Internalize these five principles. They are your guide to writing tests that stay
valuable as the project grows.

## Naming and Structure

Structure and naming are not trivial details, they are what keeps a test suite
maintainable over the long run. Two simple habits do most of the work.

First, mirror your production code with your tests. For every source file you
create, such as `led_driver.c`, you create a corresponding test file named
`test_led_driver.c`. The layout of the tests then tells you where to look the
moment something breaks.

Second, treat the name of each test function as your first line of documentation.
A well-named test tells you exactly what failed without your ever having to open
the test code, which is invaluable once a project has hundreds of them. By reading
the name alone, you should know what the test exercises and what a pass or a
failure is meant to prove.

Compare these. The good tests are longer, but they optimize for clarity:

```c
test_driver_turn_on_sets_the_correct_output_data_register_bit
test_driver_init_enables_the_gpio_clock
```

The bad ones are shorter and feel elegant, but they earn their place on the list
by telling you nothing:

```c
test_led_one   /* what about it? what is being verified? */
check_port     /* far too generic */
```

A short name that hides intent is not a win. Keep these conventions in mind and the
test names become living documentation that always matches what the code actually
does.

## Essential Unity Assertions

Unity is a lightweight unit-testing framework for C built around expressive
assertion macros. They validate program behavior, print helpful diagnostics, and
stop a failing test immediately, so a fault is caught right at the point of error.
Think of these macros as your toolbox for checking results: you reach for only a
handful most of the time, but knowing those well covers nearly every case.

The set is broad, with assertions for booleans, integers of every width, strings,
bitmasks, ranges, relational comparisons, and pointers. Most come in type-specific
forms, which makes the intent explicit about the width you actually expect. Each
family gets its own section below, but they all share the same shape: an expected
value, the actual value, and a clear pass or fail.

Almost every assertion also has a `_MESSAGE` variant that takes a trailing custom
string, printed only when the check fails. It is an easy way to leave yourself a
note about what a failure actually means:

```c
TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x3F, value, "config register not initialized");
```

Finally, `TEST_FAIL_MESSAGE` lets you mark a code path that should never be
reached:

```c
TEST_FAIL_MESSAGE("this branch should be unreachable");
```

Placing it on a path you believe is impossible turns an assumption into a checked
guarantee: if execution ever lands there, the test fails and tells you why. It is a
small way to keep the test logic itself honest.

## Boolean and Pointer Assertions

The first family of assertions deals with the truthiness of a value and the
validity of a pointer. They are general-purpose checks, and they rest on a simple
fact about C: any non-zero value is true and zero is false. It is the same idea as
writing `while (1)` instead of `while (true)`, so in embedded code any number above
zero counts as true.

| Assertion | Passes when |
|---|---|
| `TEST_ASSERT(condition)` | the condition is true (non-zero) |
| `TEST_ASSERT_TRUE(condition)` | the condition is true, a readable alias for `TEST_ASSERT` |
| `TEST_ASSERT_FALSE(condition)` | the condition is false (zero) |
| `TEST_ASSERT_UNLESS(condition)` | the condition is false, it inverts the condition |
| `TEST_ASSERT_NULL(pointer)` | the pointer is `NULL` |
| `TEST_ASSERT_NOT_NULL(pointer)` | the pointer is not `NULL` |

The `registry` example puts all six to work. The module is tiny: `Registry_IsKnown`
answers a yes-or-no question, and `Registry_NameOf` hands back a pointer to a name
or `NULL` when the id is unknown, which is exactly the shape these assertions are
built for.

```c
TEST(Registry, ReportsAKnownId)
{
    /* TEST_ASSERT is the base check, TEST_ASSERT_TRUE is its readable alias. */
    TEST_ASSERT(Registry_IsKnown(0));
    TEST_ASSERT_TRUE(Registry_IsKnown(2));
}

TEST(Registry, ReportsAnUnknownId)
{
    /* TEST_ASSERT_UNLESS inverts the condition, just like asserting false. */
    TEST_ASSERT_FALSE(Registry_IsKnown(99));
    TEST_ASSERT_UNLESS(Registry_IsKnown(99));
}

TEST(Registry, KnownIdReturnsAName)
{
    TEST_ASSERT_NOT_NULL(Registry_NameOf(1));
}

TEST(Registry, UnknownIdReturnsNoName)
{
    TEST_ASSERT_NULL(Registry_NameOf(99));
}
```

The full module lives in `src/registry.c` and `tests/registry_test.c`. Run `make`
to watch the four cases go green.

## Integer Equality Assertions

The next family checks that two integers are equal, in both signed and unsigned
flavors and at any width. They all take the same two arguments: the expected value
first, then the actual value, where the actual value is usually whatever a function
or computation returned.

| Assertion | Checks |
|---|---|
| `TEST_ASSERT_EQUAL(expected, actual)` | equality at the platform's native `int` width, an alias for `TEST_ASSERT_EQUAL_INT` |
| `TEST_ASSERT_EQUAL_INT(expected, actual)` | signed integer equality |
| `TEST_ASSERT_EQUAL_INT8/16/32/64` | signed equality at a specific width |
| `TEST_ASSERT_EQUAL_UINT(expected, actual)` | unsigned integer equality |
| `TEST_ASSERT_EQUAL_UINT8/16/32/64` | unsigned equality at a specific width |
| `TEST_ASSERT_NOT_EQUAL(expected, actual)` | that the two values differ |

`TEST_ASSERT_EQUAL` follows the native `int` of the platform, so on an Arm target
where `int` is 32 bits it behaves like the 32-bit check. Reach for the width-specific
variants when you want the assertion pinned to an exact type rather than whatever
the platform happens to use.

The `gpio_reg` example counts set bits and asserts the result as a plain integer:

```c
TEST(GpioReg, CountsSetPinsAsAnInteger)
{
    /* TEST_ASSERT_EQUAL is the alias for the platform int width. */
    TEST_ASSERT_EQUAL(3, GpioReg_CountSetPins(0x0Eu));
    TEST_ASSERT_EQUAL_UINT8(0, GpioReg_CountSetPins(0x00u));
    TEST_ASSERT_NOT_EQUAL(1, GpioReg_CountSetPins(0x0Eu));
}
```

## Hexadecimal Equality Assertions

Hex assertions compare the same integer values, but they view and print them as
hexadecimal. That makes them the natural choice for inspecting register contents and
bit-packed values, since the failure message lines up directly with a datasheet.

| Assertion | Checks |
|---|---|
| `TEST_ASSERT_EQUAL_HEX(expected, actual)` | hex value equality at the native width |
| `TEST_ASSERT_EQUAL_HEX8/16/32/64` | hex equality at a specific width |

Setting a pin in the `gpio_reg` example produces a register value we verify in hex:

```c
TEST(GpioReg, SettingAPinProducesTheExpectedRegister)
{
    /* HEX variants print the failure in hex, lined up with the datasheet. */
    TEST_ASSERT_EQUAL_HEX32(0x00000001u, GpioReg_SetPin(0x00000000u, 0));
    TEST_ASSERT_EQUAL_HEX8(0x81u, (uint8_t)GpioReg_SetPin(0x01u, 7));
}
```

## Bitmask and Bit-Level Assertions

When you care about specific bits rather than the whole value, Unity has assertions
that validate masked fields or individual bits. These are the workhorses of driver
tests.

| Assertion | Checks |
|---|---|
| `TEST_ASSERT_BITS(mask, expected, actual)` | only the bits under `mask`, compared against `expected` |
| `TEST_ASSERT_BITS_HIGH(mask, actual)` | every bit under `mask` is one |
| `TEST_ASSERT_BITS_LOW(mask, actual)` | every bit under `mask` is zero |
| `TEST_ASSERT_BIT_HIGH(bit, actual)` | the single bit at index `bit` is one |
| `TEST_ASSERT_BIT_LOW(bit, actual)` | the single bit at index `bit` is zero |

Note the difference between the plural and singular forms: `BITS` takes a mask and
acts on every bit it selects, while `BIT` takes an index, so `TEST_ASSERT_BIT_HIGH(4, reg)`
checks bit number four specifically.

Driving a single pin in the `gpio_reg` example shows both forms at once:

```c
TEST(GpioReg, SettingAPinDrivesTheRightBits)
{
    uint32_t reg = GpioReg_SetPin(0x00u, 4);

    /* Single bit: index 4 is high, index 0 stays low. */
    TEST_ASSERT_BIT_HIGH(4, reg);
    TEST_ASSERT_BIT_LOW(0, reg);

    /* Masked fields: only bit 4 of the low nibble mask is high. */
    TEST_ASSERT_BITS_HIGH(0x10u, reg);
    TEST_ASSERT_BITS_LOW(0x0Fu, reg);
    TEST_ASSERT_BITS(0xFFu, 0x10u, reg);
}
```

The whole module lives in `src/gpio_reg.c` and `tests/gpio_reg_test.c`.