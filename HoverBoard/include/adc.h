#ifndef ADC_H
#define ADC_H

// Include Librairies and Header
#include <uart.h>

// Setup Structure
static volatile struct
{
    uint8_t ADC0;
    uint8_t ADC1;
    uint8_t ADC2;
    uint8_t ADC3;
    uint8_t ADC4;
    uint8_t ADC5;
    uint8_t ADC6;
    uint8_t ADC7;
} ADC_data;

// Initialize Global Variables
static volatile uint8_t ADC_sample;
static volatile uint16_t* ADC_acc, ADC_Accumulate;

// Define Functions
void adc_init(uint8_t channel, uint8_t en_IRQ); // Initialize ADC
uint16_t adc_US(uint16_t* reading , uint8_t max_sample); // Set up ADC for US
uint16_t adc_IR(uint16_t* reading , uint8_t max_sample); // Set up ADC for IR
ISR(ADC_vect); // Populate ADC_data
#endif