#include "adc.h"

void adc_init()
{
    ADMUX |= (1<<REFS0); // Vref = AVcc
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN); // Prescaler to 128 and enable ADC conversion
}

uint16_t readADC(uint8_t channel)
{
    
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Choose ADC channel with safety mask
    ADCSRA |= (1<<ADSC); // Sincgle Conversion mode

    // Wait until conversion ends
    while(ADCSRA & (1<<ADSC));
    return ADC; 
}