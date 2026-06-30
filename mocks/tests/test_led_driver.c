#include "unity.h"          /* Unity API                                  */
#include "mock_gpio.h"      /* the GPIO mock: *_Expect plus lifecycle     */
#include "led_driver.h"     /* the production code under test             */

#define LED_PIN  5u

/*
 * Every test follows the same three acts:
 *   1. expectation: program the mock with the GPIO calls it should see
 *   2. action:      call the driver function under test
 *   3. verification: tearDown asks the mock whether it all happened
 */

void setUp(void)
{
    mock_gpio_Init();
}

void tearDown(void)
{
    mock_gpio_Verify();     /* the automatic third act */
    mock_gpio_Destroy();
}

/* init should drive the pin low so the LED starts off */
void test_init_drives_the_led_pin_low(void)
{
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);

    led_driver_init(LED_PIN);
}

/* turn_on writes HIGH to the pin chosen at init */
void test_turn_on_writes_high_to_the_led_pin(void)
{
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);    /* from init  */
    GPIO_Write_Expect(LED_PIN, GPIO_HIGH);   /* from turn_on */

    led_driver_init(LED_PIN);
    led_driver_turn_on();
}

/* turn_off writes LOW to the pin */
void test_turn_off_writes_low_to_the_led_pin(void)
{
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);    /* from init     */
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);    /* from turn_off */

    led_driver_init(LED_PIN);
    led_driver_turn_off();
}

/* toggle reads a LOW level and therefore writes HIGH */
void test_toggle_from_low_reads_then_writes_high(void)
{
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);            /* init                     */
    GPIO_Read_ExpectAndReturn(LED_PIN, GPIO_LOW);    /* toggle reads the level   */
    GPIO_Write_Expect(LED_PIN, GPIO_HIGH);           /* toggle writes the opposite */

    led_driver_init(LED_PIN);
    led_driver_toggle();
}

/* toggle reads a HIGH level and therefore writes LOW */
void test_toggle_from_high_reads_then_writes_low(void)
{
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);            /* init   */
    GPIO_Read_ExpectAndReturn(LED_PIN, GPIO_HIGH);   /* toggle reads the level */
    GPIO_Write_Expect(LED_PIN, GPIO_LOW);            /* toggle writes the opposite */

    led_driver_init(LED_PIN);
    led_driver_toggle();
}
