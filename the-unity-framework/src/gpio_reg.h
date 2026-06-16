#ifndef GPIO_REG_H
#define GPIO_REG_H

#include <stdint.h>

/* Returns a copy of reg with the bit at position pin set to one. */
uint32_t GpioReg_SetPin(uint32_t reg, uint8_t pin);

/* Returns a copy of reg with the bit at position pin cleared to zero. */
uint32_t GpioReg_ClearPin(uint32_t reg, uint8_t pin);

/* Counts how many bits are set in reg. */
uint8_t GpioReg_CountSetPins(uint32_t reg);

#endif /* GPIO_REG_H */
