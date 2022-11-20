#ifndef SERVO_H
#define SERVO_H

// Define Libraries
#include "adc.h"
#include "uart.h"
#include <util/delay.h>

// Define Fan Pins
#define SERVO PB1 // Connected to OC1A

// Defne Functions
void SERVO_init(); // Initalize Servo Motor
void SERVO_turn(int16_t angle); // Turn Motor in Given Angle

#endif