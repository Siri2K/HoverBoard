#include "led.h"

void LED_Init()
{
    // Intialize Pins
    DDRB |= (1<<YELLOW_LED) | (1<<D3_LED);

    // Set PB3 to PWM
    TCCR2A |= (1<<COM0A1)|(1<<COM0B1);
    TCCR2A |= (1<<WGM20);
    OCR2A = 0;
    TCCR2B |= ((1<<CS21)|(1<<CS20)); 
}

void LED_Brightness(int16_t distance)
{
    int16_t brightness = 255*(40-distance)/(40-15);

    if(distance < 15)
    {
        // Set Brightness
        brightness = 255;

        // Turn ON LED's
        PORTB |= (1<<YELLOW_LED);
    }
    else if(distance > 40)
    {
        // Set Brightness
        brightness = 0;

        // Turn ON LED's
        PORTB |= (1<<YELLOW_LED);
    }
    else
    {
        // Set Brightness
        brightness = 255*(40-distance)/(40-15);
        // Turn ON LED's
        PORTB &= ~(1<<YELLOW_LED);
    }
    OCR2A = brightness;
}
