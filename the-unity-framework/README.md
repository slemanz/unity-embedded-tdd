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
forms, which is what makes the intent explicit about the width you actually expect:

```c
TEST_ASSERT_EQUAL_UINT8(0x3F, value);
TEST_ASSERT_EQUAL_INT16(-1, delta);
TEST_ASSERT_EQUAL_UINT32(0xDEADBEEF, id);
TEST_ASSERT_EQUAL_HEX16(0x1234, reg);
```

The `HEX` variants are especially good for verifying register values, since the
failure message prints in hex and lines up directly with the datasheet.

For simpler conditions there are boolean and pointer checks:

```c
TEST_ASSERT_TRUE(condition);
TEST_ASSERT_FALSE(condition);
TEST_ASSERT_NULL(pointer);
TEST_ASSERT_NOT_NULL(pointer);
```

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
