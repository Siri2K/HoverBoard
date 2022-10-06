#ifndef ULTRASONIC_H
#define ULTRASONIC_H

// Include Libraries and Headers
#include "adc.h"
#include "uart.h"
//#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/wdt.h>

// Define Pins
#define TRIGGER_PIN PB3
#define ECHO_PIN PD2

// Define Timer values
#define PWM_TOP 2500

// Initialize Global Variables
static volatile int pulse = 0;

// Define Pulse Structure
static volatile struct
{
    uint16_t pulse0;
    uint16_t pulse1;

    uint16_t tstart0;
    uint16_t tstart1;
    uint16_t tend0;
    uint16_t tend1;
}pulse_data;

// Declare functions
void US_init(); // Initialize Ultrasonic Sensor
void trigger(); // Trigger Pulse
ISR(INT0_vect); // Get Echo Pulse 
uint16_t US_getPulse(); // Get Timing Pulse
int US_getDistance(); // Get Distance from US

#endif