#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/* Fills count samples with the same baseline value. */
void Adc_Fill(uint16_t *samples, uint16_t baseline, uint8_t count);

/* Converts a 12-bit raw reading (0..4095) to volts on a 3.3V reference. */
float Adc_ToVolts(uint16_t raw);

#endif /* ADC_H */
