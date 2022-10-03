#include "adc.h"

void adc_init()
{
    ADMUX |= (1<<REFS0); // Vref = AVcc
    ADCSRA = 0x87; // ADCSRA : 1000 0111 -> Prescaler to 128 and enable ADC conversion
}

uint16_t readADC(uint8_t channel)
{
    
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Choose ADC channel with safety mask
    ADMUX |= (1<<ADSC); // Sincgle Conversion mode

    // Wait until conversion ends
    while(ADMUX & (1<<ADSC));
    return ADC; 
}

