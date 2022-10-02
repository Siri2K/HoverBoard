#include "adc.h"


void adc_init(uint8_t channel,uint8_t en_IRQ)
{
    ADMUX = (1<<ADLAR) | (channel & 0xFF);

    ADCSRA |= (1<<ADEN); 

    if(en_IRQ)
    {
        ADCSRA |= (1<<ADIE);
    }

    ADCSRA |= 0x67; // ADCSRA = 0110 0111; 
    
    /*
    ADCSRA bit map:
    - 0 to 2 : ADC Prescaller Select Bits 
    - 3 : ADC Interrupt Enable
    - 4 : ADC Interrupt Flag
    - 5 : ADC Auto Trigger Enable
    - 6 : ADC start Conversion
    - 7 : ADC Enable
    */
}

ISR(ADC_vect)
{
    PORTB ^= (1<<PB3); // Check ISR Timing

    // Get First Readings
    uint8_t ADC_sample_max = 4;
    if(ADC_sample == 0)
    {
        ADC = 0; // Reset Accumulator
        ADC_sample++;
    }

    // Accumulate Readings
    if(ADC_sample <= ADC_sample_max)
    {
        ADC_acc[0]+=ADCH;
        ADC_sample++;
        return;
    }

    // Filter Data
    if(ADC_sample > ADC_sample_max)
    {
        ADC_sample = 0;
        ADC_acc[0] = ADC_acc[0]/ADC_sample_max;

        // Store Data into ADC_channel
        switch(ADMUX & 7)
        {
            case 0: // Channel 0
            {
                ADMUX = (ADMUX & 0xF0) | 0x01; // Switch to the Next Channel
                ADC_data.ADC0 = (uint8_t)ADC_acc[0]; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 1: // Channel 1
            {
                ADMUX = (ADMUX & 0xF0) | 0x02; // Switch to the Next Channel
                ADC_data.ADC1 = (uint8_t)ADC_acc[0]; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 2: // Channel 2
            {
                ADMUX = (ADMUX & 0xF0) | 0x03; // Switch to the Next Channel
                ADC_data.ADC2 = (uint8_t)ADC_acc[0]; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 3: // Channel 3
            {
                ADMUX = (ADMUX & 0xF0) | 0x06; // Switch to the Next Channel
                ADC_data.ADC3 = (uint8_t)ADC_acc[0]; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 6: // Channel 4
            {
                ADMUX = (ADMUX & 0xF0) | 0x07; // Switch to the Next Channel
                ADC_data.ADC6 = (uint8_t)ADC_acc[0]; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 7: // Channel 5
            {
                ADMUX = (ADMUX & 0xF0) | 0x00; // Switch to the Next Channel
                ADC_data.ADC7 = (uint8_t)ADC_acc[0]; // Stored Filter Reading in the ADC_DATA
                return;
            }

            default: // Channel 0
            {
                ADMUX = (ADMUX & 0xF0) | 0x00; // Switch to the Next Channel
            }
        }
    }
}
