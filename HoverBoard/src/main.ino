// Set the Clock
#define F_CPU 160000000UL

// Include File Path
#include "uart.h"

// Include Arduino Specific Librairy
#include <avr/io.h>
#include <util/delay.h>

// Include C Library
#include <stdio.h>


// Define US pins
#define Trigger_Pin PB3
#define Echo_Pin PD2 

// Global Variables
int timer_overflow = 0;

// Create Flags Structure
volatile struct {
  uint8_t TX_finished:1;
  uint8_t sample:1;
  uint8_t mode:1;
  uint8_t stop:1;
//  uint8_t ADC_ready:1;
  uint8_t T1_ovf0:2;
  uint8_t T1_ovf1:2;
} flags;


// Setup Timer Overflow
ISR(TIMER0_OVF_vect)
{
    timer_overflow++; // Up Timer Oveflow count
}

// Loop Trigger Pin
void Trigger()
{
    PORTB |= (1<<Trigger_Pin);
    _delay_us(10);
    PORTB &= ~(1<<Trigger_Pin);
   
}

void Echo()
{
    // Rising Edge Timer 
    TCNT1 = 0;
    TCCR1B = 0x41; // TCCR1B = 0100 0001
    TIFR1 = (1<<ICF1)|(1<<TOV1); // Clear ICP &  Timer OverFlow Flag
    timer_overflow = 0;

    // Rising Edge
    while((TIFR1 & (1<<ICF1)) == 0);
    
    // Falling Edge Timer 
    TCNT1 = 0;
    TCCR1B = 0x01; // TCCR1B = 0000 0001
    TIFR1 = (1<<ICF1)|(1<<TOV1); // Clear ICP &  Timer OverFlow Flag
    timer_overflow = 0;

    // Falling Edge
    while((TIFR1 & (1<<ICF1)) == 0);
}

// Send String to UART
#ifdef DEBUG

void sendString(uint8_t* str)
{
    while(!flags.TX_finished)
    {
        msg = str;
        UDR0=*msg;
        flags.TX_finished = 1;
    }
}
#endif DEBUG

int main()
{   
    
    // Declare and Intialize Variables
    double distance = 0; // Object Distance
    long count = 0; // Pulse Size Count
    double conversion = 34300/2*(1/F_CPU); // Convert From Timer to Distance
    
    
    // Setup Output Pin
    DDRB = 0x04; // DDRB = 0000 0100
    DDRD &= ~(1<<Echo_Pin); // DDRD = 0000 0000

    // Setup UART
    #ifdef DEBUG
        UART_init();
        flags
    #endif

    // Initialize Timer
    sei(); // Allow Global Intterupt
    TIMSK1 = (1<<TOIE1); // Enable Timer 1 Overflow Interrupt
    TCCR1A = 0; // Set all bits to 0

    while(true)
    {
        // Send A pulse to Trigger pin
        Trigger();
         _delay_us(10);

        // Read Value from Echo Pin & Find Distance
         Echo();
         count = ICR1 + (65535*timer_overflow);
         distance = (double)count*conversion;

    }
}

