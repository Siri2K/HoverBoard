#ifndef ADC_H
#define ADC_H

// Include Libraries
#include <avr/io.h>

// Define Functions
void adc_init(); // Initialize ADC
uint16_t readADC(uint8_t channel); // Read ADC in specific ADC channel

#endif