#include "gpio_reg.h"

uint32_t GpioReg_SetPin(uint32_t reg, uint8_t pin)
{
    return reg | (1u << pin);
}

uint32_t GpioReg_ClearPin(uint32_t reg, uint8_t pin)
{
    return reg & ~(1u << pin);
}

uint8_t GpioReg_CountSetPins(uint32_t reg)
{
    uint8_t count = 0;

    while (reg)
    {
        count += reg & 1u;
        reg >>= 1;
    }

    return count;
}
