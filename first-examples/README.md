# A First Example: The Calculator

This module is a hands-on walkthrough of the Red-Green-Refactor cycle using
Unity. Instead of presenting a finished function and a finished test file, it
retraces the path that produced them, one test at a time, so you can see how the
implementation grows only as far as the tests demand.

The module under test is tiny on purpose: a single `Calculator_Multiply`
function. What matters here is not the arithmetic, it is the rhythm of writing a
failing test, making it pass with the least code possible, and only then
cleaning up.

## Running the Tests

```sh
make        # compile and run the test suite
make clean  # remove build artifacts
```

A successful run ends with `OK`. Any failure prints the file, the line, and the
expected versus actual values, which is exactly the feedback you want while
driving the code from tests.

## The Files

```
first-examples/
├── Makefile               # Builds and runs the tests
├── src/
│   ├── calculator.c       # The production code we grow test by test
│   └── calculator.h       # The public interface
├── tests/
│   ├── calculator_test.c  # The test group and its cases
│   └── AllTestRunner.c    # Registers the group and starts Unity
└── unity/                 # Unity + CMock framework (vendored)
```

Each test lives in the `Calculator` test group. A group bundles related cases
together and gives them a shared `TEST_SETUP` and `TEST_TEAR_DOWN`, which run
before and after every case. Both are empty here because the calculator has no
state to prepare or release, but they are kept in place so the structure is ready
the moment a test needs them.

## Growing the Function Test by Test

What follows is the same module rebuilt from nothing. Read it top to bottom and
you will watch the implementation earn every line it contains.

### Step 1: Multiplying by zero

We start with the simplest behavior we can describe, and we describe it before
the function even exists.

```c
TEST(Calculator, MultiplyingByZeroGivesZero)
{
    TEST_ASSERT_EQUAL_INT(0, Calculator_Multiply(1, 0));
    TEST_ASSERT_EQUAL_INT(0, Calculator_Multiply(0, 2));
}
```

This is the **Red** step. The code does not compile yet, which counts as a
failing test: the goal is undefined and the test makes that obvious. To reach
**Green** we add the absolute minimum that satisfies the assertions, and nothing
more:

```c
int Calculator_Multiply(int a, int b)
{
    return 0;
}
```

Returning a constant zero feels like cheating, and that is the point. The test
only asks for zero, so zero is all we are entitled to write. A passing test now
proves the harness works and the function is wired up correctly. Resist the urge
to multiply yet, because no test is asking for it.

### Step 2: Multiplying positive numbers

Now we add a test that the constant cannot satisfy.

```c
TEST(Calculator, MultipliesPositiveNumbers)
{
    TEST_ASSERT_EQUAL_INT(5, Calculator_Multiply(5, 1));
    TEST_ASSERT_EQUAL_INT(8, Calculator_Multiply(2, 4));
}
```

This goes Red immediately: `return 0` answers five and eight with zero. The
smallest honest fix is to actually multiply the arguments.

```c
int Calculator_Multiply(int a, int b)
{
    return a * b;
}
```

Both tests pass again. The earlier zero case still holds, because anything times
zero is zero, so we have moved forward without breaking what already worked. That
running safety net is the whole reason the previous step mattered.

### Step 3: Multiplying negative numbers

We push on the behavior with signs.

```c
TEST(Calculator, MultipliesNegativeNumbers)
{
    TEST_ASSERT_EQUAL_INT(-20, Calculator_Multiply(10, -2));
    TEST_ASSERT_EQUAL_INT(100, Calculator_Multiply(-10, -10));
}
```

This time the test passes the moment we write it, because `a * b` already handles
negatives correctly. A test that goes Green on the first try is still valuable: it
documents an expectation and locks the behavior in, so a future change cannot
quietly break it. The implementation stays exactly as it was.

### Step 4: Saturating on overflow

The last test describes what should happen when the true product is larger than an
`int` can hold.

```c
TEST(Calculator, SaturatesWhenTheResultOverflows)
{
    TEST_ASSERT_EQUAL_INT(INT_MAX, Calculator_Multiply(INT_MAX, 2));
}
```

`INT_MAX * 2` overflows a 32-bit `int`, so `a * b` would produce undefined
behavior rather than the clamped value we expect. To make this pass we compute the
product in a wider type, check whether it exceeds the range, and saturate to
`INT_MAX` when it does.

```c
int Calculator_Multiply(int a, int b)
{
    long long result = (long long)a * (long long)b;

    if (result > INT_MAX)
        return INT_MAX;

    return (int)result;
}
```

This is the version that ships, in `src/calculator.c`. Every branch in it exists
because a specific test asked for it. Nothing was added speculatively, and the
three earlier tests still pass, which is how we know the overflow guard did not
disturb the ordinary cases.

## The Takeaway

Notice what never happened: at no point did we sit down and write the final
function from memory. Each line appeared in response to a concrete, failing test,
and each green bar gave us the confidence to take the next small step. That is the
loop the rest of this repository builds on, with test doubles and mocks layered on
top once real hardware enters the picture.
