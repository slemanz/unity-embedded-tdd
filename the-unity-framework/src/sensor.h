#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

/* Returns the integer average of count samples. */
uint16_t Sensor_Average(const uint16_t *samples, uint8_t count);

#endif /* SENSOR_H */
