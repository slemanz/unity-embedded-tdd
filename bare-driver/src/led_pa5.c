#include "fake_stm32f4xx.h"         /* use tiny CMSIS fake on host */
#include "led_pa5.h"                /* Driver API */

/* Bit helpers and constants */
#define GPIOAEN             (1u << 0)               /* RCC AHB1 enable bit for GPIOA */
#define LED_PIN_INDEX       5u                      /* PA5 user LED index */
#define LED_PIN_MASK        (1u << LED_PIN_INDEX)   /* PA5 bit mask */

#define MODE_BITS(pin)      (0x3u << ((pin) * 2u))  /* 2-bit field mask in MODER */
#define MODE_OUT(pin)       (0x1u << ((pin) * 2u))  /* 01b for output mode */
#define PUPD_BITS(pin)      (0x3u << ((pin) * 2u))  /* 2-bit field mask in PUPDR */
#define PUPD_NODE(pin)      (0x0u << ((pin) * 2u))  /* 00b for no pull */


/* Configure PA5 as push-pull output, medium speed, no pull, start OFF */
void led_init(void)
{
    RCC->AHB1ENR |= GPIOAEN;

    GPIOA->MODER = (GPIOA->MODER & ~MODE_BITS(LED_PIN_INDEX))
                    | MODE_OUT(LED_PIN_INDEX);      /* set PA5 output mode */

}
