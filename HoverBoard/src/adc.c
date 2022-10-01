#include "adc.h"

// Define Sample 
#define ADC_sample_max 4

void adc_init(uint8_t channel, uint8_t en_IRQ)
{
    ADMUX = (1<<ADLAR) | (channel & 0xFF);
    ADCSRA = (1<<ADEN);

    if(en_IRQ)
    {
        ADCSRA |= (1<<ADIE); // Enable ADC Complete Interrupt
    }

    ADCSRA |= 0x07; // Enable ADC Clock Prescaller
    ADCSRA |= (1<<ADATE); // Continuous Runnning Mode
    ADCSRA |= (1<<ADSC); // Start ADC
}

uint16_t adc_US(uint16_t* reading , uint8_t max_sample)
{
    uint16_t max_value = 0;
    uint16_t maxCount = 0;
    

    // Get Mode
    for(uint8_t i = 0; i<max_sample; i++)
    {
        uint16_t count = 0;

        for(uint8_t j = 0; j<max_sample; j++)
        {
            if(reading[j] == reading[i])
            {
                count++;
            }
        }

        if(count > maxCount) // Update Max COunt
        {
            maxCount = count;
            max_value = reading[i];
        }
    }

    return max_value;
}

uint16_t adc_IR(uint16_t* reading , uint8_t max_sample)
{
   uint16_t ADC_total = 0;
   uint8_t i=0;

   while(reading[i] != NULL)
   {
     ADC_total+=reading[i];
     i++;
   }

   return ADC_total/max_sample;
}

ISR(ADC_vect)
{
    PORTB ^= (1<<PB3); // Check ISR Timing

    // Get First Readings
    if(ADC_sample == 0)
    {
        ADC = 0; // Reset Accumulator
        ADC_sample++;
    }

    // Accumulate Readings
    if(ADC_sample <= ADC_sample_max)
    {
        ADC_acc[ADC_sample] = ADCH;
        ADC_sample++;
        return;
    }

    // Filtering Data
    if(ADC_sample > ADC_sample_max)
    {
        ADC_Accumulate = adc_US(ADC_acc, 4); // Accumulate Data For Ultrasonic Sensor
        /* ADC_Accumulate = adc_US(ADC_acc, 1); */ // Accumulate Data For IR Distance Sensor

        // Check which ADC channel is the data stored
        switch(ADMUX & 7)
        {
            case 0: // Channel 0
            {
                ADMUX = (ADMUX & 0xF0) | 0x01; // Switch to the Next Channel
                ADC_data.ADC0 = (uint8_t)ADC_Accumulate; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 1: // Channel 1
            {
                ADMUX = (ADMUX & 0xF0) | 0x02; // Switch to the Next Channel
                ADC_data.ADC1 = (uint8_t)ADC_Accumulate; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 2: // Channel 2
            {
                ADMUX = (ADMUX & 0xF0) | 0x03; // Switch to the Next Channel
                ADC_data.ADC2 = (uint8_t)ADC_Accumulate; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 3: // Channel 3
            {
                ADMUX = (ADMUX & 0xF0) | 0x06; // Switch to the Next Channel
                ADC_data.ADC3 = (uint8_t)ADC_Accumulate; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 6: // Channel 4
            {
                ADMUX = (ADMUX & 0xF0) | 0x07; // Switch to the Next Channel
                ADC_data.ADC6 = (uint8_t)ADC_Accumulate; // Stored Filter Reading in the ADC_DATA
                return;
            }

            case 7: // Channel 5
            {
                ADMUX = (ADMUX & 0xF0) | 0x00; // Switch to the Next Channel
                ADC_data.ADC7 = (uint8_t)ADC_Accumulate; // Stored Filter Reading in the ADC_DATA
                return;
            }

            default: // Channel 0
            {
                ADMUX = (ADMUX & 0xF0) | 0x00; // Switch to the Next Channel
            }
        }
    }
}