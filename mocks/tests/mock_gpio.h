#ifndef MOCK_GPIO_H
#define MOCK_GPIO_H

#include "gpio.h"

/*
 * A hand-written stand-in for the GPIO module, shaped like the mocks CMock
 * generates from a header. It is split into three jobs:
 *
 *   - lifecycle: mock_gpio_Init / mock_gpio_Verify / mock_gpio_Destroy
 *   - expectations: the *_Expect functions you program before acting
 *   - the contract itself: GPIO_Write / GPIO_Read, supplied by mock_gpio.c
 *
 * The mock records the calls you expect, checks each real call against the next
 * expectation in order, and at Verify time fails the test if any expected call
 * never happened.
 */

void mock_gpio_Init(void);      /* clear all recorded expectations (call in setUp)   */
void mock_gpio_Verify(void);    /* assert every expected call happened (call in tearDown) */
void mock_gpio_Destroy(void);   /* release the mock; here it just resets state        */

/* Expect a GPIO_Write with these exact arguments. */
void GPIO_Write_Expect(uint8_t pin, GpioState state);

/* Expect a GPIO_Read on this pin, and hand back value_to_return when it happens. */
void GPIO_Read_ExpectAndReturn(uint8_t pin, GpioState value_to_return);

#endif /* MOCK_GPIO_H */
