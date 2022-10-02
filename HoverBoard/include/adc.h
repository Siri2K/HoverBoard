#ifndef ADC_H
#define ADC_H

// Include Libraries & Headers
#include "uart.h"
#include <avr/io.h>

// Define ADC_data Structure
static volatile struct
{
    uint8_t ADC0; // Channel 0
    uint8_t ADC1; // Channel 1
    uint8_t ADC2; // Channel 2
    uint8_t ADC3; // Channel 3
    uint8_t ADC6; // Channel 6
    uint8_t ADC7; // Channel 7

} ADC_data;

// Define Variables
static volatile uint8_t ADC_sample;
static volatile uint16_t* ADC_acc;

// Define function
void adc_init(uint8_t channel,uint8_t en_IRQ); // Initialize ADC
ISR(ADC_vect); // Save Reading into ADC Channel

#endif