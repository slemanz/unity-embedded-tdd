#include "fake_stm32f4xx.h"

RCC_TypeDef RCC_ = (RCC_TypeDef){0}; /* zero-init fake RCC */
GPIO_TypeDef GPIOA_ = (GPIO_TypeDef){0}; /* zero-init fake GPIOA */