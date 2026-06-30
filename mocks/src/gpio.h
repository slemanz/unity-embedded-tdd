#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*
 * The GPIO contract. This is the only thing the LED driver knows about the
 * outside world. On a real target a gpio.c would drive memory-mapped registers
 * behind these prototypes. In our tests we never compile that file: the mock
 * stands in for it and verifies how the driver calls these functions.
 */

typedef enum
{
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
} GpioState;

void      GPIO_Write(uint8_t pin, GpioState state);
GpioState GPIO_Read(uint8_t pin);

#endif /* GPIO_H */
