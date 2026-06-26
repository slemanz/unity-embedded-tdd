#ifndef LED_PA5_H
#define LED_PA5_H

/* Public API for the PA% LED Driver used in tests */
void led_init(void);                    /* Configure PA5 as output and start OFF */
void led_on(void);                      /* atomically set PA5 high using BSRR */
void led_off(void);                     /* atomically reset PA5 low using BSRR*/
void led_toggle(void);                  /* toggle based on current ODR level */

#endif /* LED_PA5_H */