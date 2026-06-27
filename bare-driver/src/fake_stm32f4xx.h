#ifndef FAKE_STM32F4XX_H_
#define FAKE_STM32F4XX_H_
#include <stdint.h>

/* Minimal RCC and GPIO models for host tests */
/* Keep only what led driver needs */
typedef struct {
    volatile uint32_t AHB1ENR; /* AHB1 peripheral clock enable */
}RCC_TypeDef;

typedef struct{
    volatile uint32_t MODER;    /* Mode register */
    volatile uint32_t OTYPER;   /* output type */
    volatile uint32_t OSPEED;   /* speed */
    volatile uint32_t PUPDR;    /* pull up/down */
    volatile uint32_t IDR;      /* input data */
    volatile uint32_t ODR;      /* output data */
    volatile uint32_t BSRR;     /* bit set reset */
}GPIO_TypeDef;

/* Globals that simulate cmsis style singletons */
extern RCC_TypeDef RCC_;
extern GPIO_TypeDef GPIOA_;

#define RCC         (&RCC_)
#define GPIOA       (&GPIOA_)

#endif /* FAKE_STM32F4XX_H_ */