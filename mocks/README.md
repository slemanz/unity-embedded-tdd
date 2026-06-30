# Mocks and Test Doubles

This module is where TDD stops being a good idea and turns into a real
superpower for embedded engineers. It is about the single biggest challenge in
embedded testing, the hardware itself, and the art of standing in for it so you
can test almost all of your logic without ever touching a physical board.

## Testing Your Logic, Not Your Multimeter

The goal of this module is to make your code believe it is talking to real
hardware, so you can exercise your logic on the host instead of on a board. You
are testing your logic, not your multimeter.

It helps to be explicit about why leaning on real hardware is a problem. Doing
so violates the core principles of a good unit test. It is not fast: flashing a
board and watching a pin is a long feedback loop. It is not independent or
repeatable, because the physical world is messy and unpredictable. And, most
importantly, you cannot easily create the failure conditions you need to test
for. You cannot ask a microcontroller to please have its I2C peripheral return a
corrupt byte on the third read. For a unit test to be effective, we have to
remove the hardware from the equation entirely.

## Test Doubles

So how do we remove the hardware? We introduce a concept called the test double.
The name comes from the movie industry, and the analogy fits well. A stunt
double is a professional who stands in for the lead actor during the dangerous
scenes. In our world, a test double is a piece of code that stands in for a real
dependency such as a hardware driver, a network stack, or a file system.

A double has the exact same interface as the real thing, the same function names
and parameters, but its implementation is written specifically for testing. That
lets us control its behavior completely. "Test double" is the broad category,
and within it there are several distinct types. You will hear these terms often,
so it is worth knowing how they differ.

## A Taxonomy of Test Doubles

A **stub** is the simplest kind. Its job is to provide canned answers to function
calls. For example, a `temperature_get()` function could be stubbed to always
return 25. It has no logic of its own, it just hands back fixed state.

A **fake** is more involved. It is a working implementation, just not one that is
production ready, like an in-memory database. A good embedded example is a fake
flash driver that writes to a RAM array instead of a physical flash chip. Fakes
are useful for integration tests where you want real behavior without the real
device.

A **mock** is different again, and more powerful. A mock is not about providing
data, it is about verifying behavior. You tell the mock up front, "I expect you
to be called exactly once, with these specific parameters," and at the end of the
test the mock reports whether that actually happened. This is how we test the
interactions between modules.

The mindset splits cleanly. A stub answers the question "what is the state?" A
mock answers the question "was I called correctly?" In short: a stub provides
canned return values, a fake is a lightweight working implementation we can use
to simulate hardware, and a mock observes and verifies that the right calls
happened in the right way.

## Generating Mocks with CMock

Understanding the theory is one thing, but writing every mock by hand is tedious
and error prone. This is where our next tool comes in: CMock, a utility written
in Ruby that automates the entire process of creating mocks for our C code. Think
of it as an on-demand stunt double generator.

CMock's job is to read an interface file, meaning a header (`.h`), and generate a
mock that implements it. You hand it a header and it produces a mock version as a
matching `.c` and `.h` pair.

The workflow is straightforward:

1. **Define the contract.** Write the header file for the module you need to
   fake. This is the critical step, because the header is what CMock parses.
2. **Point CMock at the header.** It parses the file and automatically generates a
   full mock source and header for that module. For example:

   ```sh
   ruby cmock.rb gpio.h
   ```

   From `gpio.h`, CMock produces `mock_gpio.c` and `mock_gpio.h` automatically.
3. **Use the mock.** In your test file, include `mock_gpio.h` instead of the real
   `gpio.h`, and your tests now talk to the generated double.

## Using a CMock Mock: Expect, Act, Verify

Working with a CMock mock follows a clean three-act pattern. The two acts that
matter most are setting expectations and verifying them.

The first act is **expectation**. This is the setup, where you use the special
`_Expect` functions CMock generates to program the mock with what it should see.
Before calling your code, you tell the mock exactly what to expect:

```c
GPIO_Write_Expect(USER_LED_PORT, USER_LED_PIN, GPIO_STATE_HIGH);
```

The second act is **action**. You call the production function that is supposed
to trigger that interaction:

```c
led_driver_turn_on();
```

The third act is **verification**, and this part is automatic. When the test
finishes, Unity and CMock work together to ask the mock: did everything happen
exactly as it was told to expect? If a call was missed or a parameter was wrong,
the mock fails the test and gives you a precise error message pointing at the
mismatch. That is what makes mocks such a powerful way to verify behavior.
