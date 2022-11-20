#ifndef FAN_H
#define FAN_H

// Define Libraries
#include "adc.h"
#include "uart.h"
#include <stdbool.h>

// Define Fan Pins
#define LIFT_FAN PD7 
#define DRIVE_FAN PD6 // Connect to OC0A

// Defne Functions
void FAN_init(); // Initalize Fans
void DRIVE_FAN_PWR(int16_t power);
void LIFT_FAN_PWR(bool fan_status);

#endif