# Bare-Metal Driver Testing

This module shows how to test a microcontroller peripheral driver on your own
machine, with no board attached, using Unity and a small fake of the hardware
registers. The example is a driver for the user LED on PA5 of an STM32F4, but the
technique applies to any memory-mapped peripheral.

## Why Test Bare-Metal Code on the Host

A bare-metal driver does its job by writing to memory-mapped registers: enable a
clock here, set a mode bit there, flip an output. On real silicon those registers
live at fixed addresses inside the chip, so the usual way to check your work is to
flash the board, watch an LED, and guess. That loop is slow, and it tells you
almost nothing about *which* bit you got wrong.

The trick is to notice that the driver does not care whether a register is real.
It only reads and writes addresses. So we model the registers as plain structs in
host memory, compile the driver against that model, and run the whole thing as an
ordinary program under `gcc`. Now a test can call `led_init()` and then assert,
bit by bit, exactly what landed in each register. The feedback is instant and
precise, and you never touch the board until the logic is already proven.

## The Register Fake

The fake lives in [`src/fake_stm32f4xx.h`](src/fake_stm32f4xx.h). It declares just
enough of the chip to satisfy the driver: an `RCC_TypeDef` with the `AHB1ENR`
clock-enable register, and a `GPIO_TypeDef` with the GPIO registers the driver
uses (`MODER`, `OTYPER`, `OSPEED`, `PUPDR`, `IDR`, `ODR`, `BSRR`).

The important part is the last few lines:

```c
extern RCC_TypeDef  RCC_;
extern GPIO_TypeDef GPIOA_;

#define RCC   (&RCC_)
#define GPIOA (&GPIOA_)
```

On real hardware the vendor header defines `RCC` and `GPIOA` as pointers to fixed
addresses. Here they point at two globals living in normal RAM. The driver writes
`GPIOA->MODER` either way and never knows the difference. This is the seam: swap
this one header and the same driver source compiles for the host or for the chip.

Because the registers are just globals, each test starts from a known state by
clearing them in `setUp`:

```c
void setUp(void)
{
    memset(&RCC_, 0, sizeof(RCC_));
    memset(&GPIOA_, 0, sizeof(GPIOA_));
}
```

## The Example: a PA5 LED Driver

The driver under test is [`src/led_pa5.c`](src/led_pa5.c). It exposes four
functions, each a single responsibility:

- `led_init()` enables the GPIOA clock, sets PA5 as a push-pull output at medium
  speed with no pull resistor, and drives the LED off to start.
- `led_on()` and `led_off()` drive the pin using only the matching halfword of
  `BSRR`, the atomic bit set/reset register, so they never read-modify-write `ODR`.
- `led_toggle()` reads the current level from `ODR` and writes the opposite
  halfword of `BSRR`.

The tests in [`tests/test_led_pa5.c`](tests/test_led_pa5.c) pin down this behavior
register by register. They check that `led_init` touches the right two-bit fields
and leaves neighboring pins alone, that `on`/`off`/`toggle` write the exact `BSRR`
value and nothing more, and that calling `led_init` twice is idempotent. Reading
the test file top to bottom is the fastest way to understand what the driver
promises.

## Building and Running

The Makefile compiles the driver, the fake, the tests, and Unity into one host
binary and runs it:

```sh
make        # compile and run the test suite
make clean  # remove build artifacts
```

A successful run ends with `OK`; any failure prints the file, line, and the
expected-versus-actual values, in hex for register fields. When you add a module,
extend the `OBJS` and `TEST_OBJS` lists in the Makefile and register the new test
functions in [`tests/test_runner.c`](tests/test_runner.c).
