#include "fake_stm32f4xx.h"

RCC_TypeDef RCC_ = (RCC_TypeDef){0}; /* zero-init fake RCC */
RCC_TypeDef GPIOA_ = (RCC_TypeDef){0}; /* zero-init fake GPIOA */