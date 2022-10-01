#ifndef ULTRASONIC_H
#define ULTRASONIC_H

// Include Libariers and Headers
#include "uart.h"
#include <util/delay.h>

// Define Structures
static volatile struct
{
    // Pulse
    uint16_t pulse0;
    uint16_t pulse1;

    // T_start
    uint16_t t_start0;
    uint16_t t_start1;

    // T_end
    uint16_t t_end0;
    uint16_t t_end1;

} pulse_data;


// Declare Functions 
void ultrasonic_init(); // Setup Ultrasonic Output
void trigger(); // Send 10us Pulse to Trigger Pin 
ISR(INT0_vect); // Obtain Pulse from Echo

#endif