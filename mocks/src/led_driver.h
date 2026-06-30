#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

/*
 * A tiny LED driver that owns no hardware of its own. It expresses everything
 * it wants to do as calls into the GPIO contract, which makes its behavior easy
 * to pin down with a mock.
 */

void led_driver_init(uint8_t pin);   /* remember the pin and start the LED off */
void led_driver_turn_on(void);       /* drive the pin high */
void led_driver_turn_off(void);      /* drive the pin low */
void led_driver_toggle(void);        /* read the level and flip it */

#endif /* LED_DRIVER_H */
