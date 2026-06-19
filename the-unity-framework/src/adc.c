#include "adc.h"

void Adc_Fill(uint16_t *samples, uint16_t baseline, uint8_t count)
{
    for (uint8_t i = 0; i < count; i++)
        samples[i] = baseline;
}

float Adc_ToVolts(uint16_t raw)
{
    return (float)raw * (3.3f / 4095.0f);
}
