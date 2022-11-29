#include "ultrasonic.h"

uint8_t sensor_working=0;
uint8_t rising_edge=0;
uint32_t timer_counter=0;
uint32_t pulse;
uint32_t distance;

void US_init()
{
    // Intialize Pins
    DDRB |= (1<<TRIGGER_PIN);
    DDRD &= ~(1<<ECHO_PIN);
    PORTD |= (1<<ECHO_PIN); // Enable Pull-up on PD3

    // Enable External Innterrupt
    EICRA |= (1<<ISC11)|(1<<ISC10); // Interrupt Register A 
    EIMSK |= (1<<INT1); // Enable Intterupt 1

    // Enable Timer 1
    TCCR1B = (0<<CS11)|(1<<CS10);
    TIMSK1 = 1<<TOIE1;
}

void US_Trigger()
{
    if(!sensor_working)
    {
        PORTD |= (1<<TRIGGER_PIN);
        _delay_us(10);
        PORTD &= ~(1<<TRIGGER_PIN);
        sensor_working = 1;
    }
}

SIGNAL(INT1_vect)
{
    if(sensor_working = 1)
    {
        if(rising_edge == 0) // Falling Edge
        {
            TCNT0 = 0x00;
            rising_edge = 1;
            timer_counter = 0;
        }
        else // Rising Edge
        {   
            pulse = (timer_counter*256+TCNT0);
            distance = pulse/58;
            timer_counter = 0;
            rising_edge = 0;
        }
    }
}

SIGNAL(TIMER0_OVF_vect)
{
    if(rising_edge)
    {
        timer_counter++;

        // Don't Wait too long
        uint32_t ticks = timer_counter * 256 + TCNT0;
        uint32_t max_ticks = (uint32_t)200 * 12000; // this could be replaced with a value instead of multiplying

        if (ticks > max_ticks) 
        {
            // timeout
            rising_edge = 0;          // stop counting timer values
            sensor_working = 0; // ultrasound scan done
            distance = -1; // show that measurement failed with a timeout (could return max distance here if needed)
        }
    }
}

int16_t US_getPulse()
{
    _delay_ms(50);
    US_Trigger();
    
    return pulse;
}

int16_t US_getDistance()
{
    return distance;
}
