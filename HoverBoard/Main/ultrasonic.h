#ifndef ULTRASONIC_H
#define ULTRASONIC_H

// Include Libraires
#include "uart.h"
#include "adc.h"
#include <util/delay.h>

// Define Pins
#define TRIGGER_PIN PB5
#define ECHO_PIN PD3

// Define Functions
void US_init(); // Initalize Ultrasonic Sensor
void US_Trigger(); // Send Trigger Pulse 
SIGNAL(INT1_vect); // Get Timer Duration
SIGNAL(TIMER0_OVF_vect); // Check for Overload
int16_t  US_getPulse(); // Get Pulse from Timer
int16_t  US_getDistance(); // Get Distance from Pulse

#endif