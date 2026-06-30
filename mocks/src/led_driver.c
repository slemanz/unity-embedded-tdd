#include "led_driver.h"
#include "gpio.h"

/*
 * The driver's only state is which pin the LED lives on. Every action is a call
 * into the GPIO contract, so the tests can assert on those calls instead of on
 * any real hardware.
 */
static uint8_t led_pin;

void led_driver_init(uint8_t pin)
{
    led_pin = pin;
    GPIO_Write(led_pin, GPIO_LOW);   /* leave the LED off after init */
}

void led_driver_turn_on(void)
{
    GPIO_Write(led_pin, GPIO_HIGH);
}

void led_driver_turn_off(void)
{
    GPIO_Write(led_pin, GPIO_LOW);
}

void led_driver_toggle(void)
{
    if (GPIO_Read(led_pin) == GPIO_HIGH)
    {
        GPIO_Write(led_pin, GPIO_LOW);
    }
    else
    {
        GPIO_Write(led_pin, GPIO_HIGH);
    }
}
