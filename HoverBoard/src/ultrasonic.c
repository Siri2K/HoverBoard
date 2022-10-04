#include "ultrasonic.h"

void US_init()
{
    // Setup Pins
    DDRB |= (1<<TRIGGER_PIN); // Trigger Pin is set to output
    DDRD &= (1<<ECHO_PIN); // Echo pin is Input

    // Setup Timer Interrupt
    EIMSK |= (1<<INT0); // Interrupt on INT0 enabled
    EICRA |= (1<<ISC00); // Interrupt on Rising and Falling Edges

    // Setup Timer 0
    TCCR0A |= (1<<COM0A1)|(1<<COM0B1); // Clear on Compare Match
    TCCR0A |= (1<<WGM00); // PWM, phase Correct
    OCR0A = 0;
    OCR0B = 0;
    TCCR0B |= (1<<CS01)|(1<<CS00);

}

void trigger()
{
    PORTB |= (1<<TRIGGER_PIN); // Trigger Pin High
    _delay_us(10);
    PORTB &= (1<<TRIGGER_PIN); // Trigger Pin Low
}

ISR(INT0_vect)
{
    if(PIND & (1<<ECHO_PIN)) // Rising Edge 
    {
        flags.T1_ovf0 = 0;
        pulse_data.tstart0 = TCNT1;
    }
    else if (!(PIND & (1<<ECHO_PIN))) // Falling Edge
    {
       pulse_data.tend0 = TCNT1; 

       // Calculate Pulse Size
       if(flags.T1_ovf0 == 1)  // 1 ovf
       {
        pulse_data.pulse0 = PWM_TOP-pulse_data.tstart0+pulse_data.tend0;
       }
       else if(flags.T1_ovf0 == 2) // 2 ovf
       {
        pulse_data.pulse0 = PWM_TOP-pulse_data.tstart0+pulse_data.tend0+PWM_TOP; 
       }
       else if(flags.T1_ovf0 == 0) // No Overflow
       {
        pulse_data.pulse0 = pulse_data.tend0 - pulse_data.tstart0;
       }
       else
       {
         pulse_data.pulse0 = 0xFFFF; // Error 
       }
    }
}

uint16_t US_getPulse()
{
    return pulse_data.pulse0; // Get pulse in s
}

int US_getDistance(uint16_t pulse)
{
    return pulse/58; // Get distance in cm/us
}