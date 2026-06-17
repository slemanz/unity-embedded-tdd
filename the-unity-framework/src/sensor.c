#include "sensor.h"

uint16_t Sensor_Average(const uint16_t *samples, uint8_t count)
{
    uint32_t sum = 0;

    for (uint8_t i = 0; i < count; i++)
        sum += samples[i];

    return (uint16_t)(sum / count);
}
