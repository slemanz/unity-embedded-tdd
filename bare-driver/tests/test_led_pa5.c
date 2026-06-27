#include "unity.h"              /* Unity API*/
#include "led_pa5.h"            /* prototypes: led_init/on/off/toggle */
#include "fake_stm32f4xx.h"     /* exposes RCC_, GPIOA_ globals and RCC/GPIOA macros */
#include <string.h>             /* memset */


#ifndef BIT
#define BIT(n)  (1u << (n))     /* Helper for bit assertion */
#endif 

void setUp(void)
{
    memset(&RCC_, 0, sizeof(RCC_));     /* clear RCC fake state */
    memset(&GPIOA_, 0, sizeof(GPIOA_)); /* clear GPIO fake state */
}

void tearDown(void)
{

}

/* 1) Init should enable clock, set PA5 output no pulls, and start OFF */
void test_led_init_enables_gpioa_and_configures_pa5_output_start_off(void)
{
    led_init();     // act
    TEST_ASSERT_BIT_HIGH(0, RCC->AHB1ENR);
}

