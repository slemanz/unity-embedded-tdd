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