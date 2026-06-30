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
