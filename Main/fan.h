#ifndef FAN_H
#define FAN_H

// Define Libraries
#include "adc.h"
#include <stdbool.h>

// Define Fan Pins
#define LIFT_FAN PD5 // Connect to 0C0B 
#define DRIVE_FAN PD6 // Connect to OC0A

// Defne Functions
void FAN_init(); // Initalize Fans
void DRIVE_FAN_pwr(int16_t power);
void LIFT_FAN_pwr(int16_t power);
#endif