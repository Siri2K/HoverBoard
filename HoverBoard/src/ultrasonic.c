#include "ultrasonic.h"

// Define Ultrasonic Pins
#define TRIGGER (1<<PB3)
#define ECHO (1<<PD2)

// Define PWM Value
#define PWM_TOP 2500

void ultrasonic_init()
{
    // Setup Inputs
    DDRB |= TRIGGER;
    DDRD &= ECHO;
}

void trigger()
{
    PORTB |= TRIGGER;
    _delay_us(10);
    PORTB &= TRIGGER;
}

ISR(INT0_vect)
{
    if(PIND &= ECHO)
    {
        flags.T1_ovf0 = 0;
        pulse_data.t_end0 = TCNT1; 
    }

    if(!(PIND &= ECHO))
    {
        pulse_data.t_end0 = TCNT1; 

        if(flags.T1_ovf0 = 1)
        {
            pulse_data.pulse0 =  PWM_TOP - pulse_data.t_start0 + pulse_data.t_end0;
        }
        else if(flags.T1_ovf0 = 2)
        {
             pulse_data.pulse0 =  PWM_TOP - pulse_data.t_start0 + pulse_data.t_end0 + PWM_TOP;
        }
        else if(flags.T1_ovf0 = 0)
        {
             pulse_data.pulse0 =  pulse_data.t_end0 - pulse_data.t_start0;
        }
        else
        {
            pulse_data.pulse0 = 0xFFFF; // Error
        }
    }
}