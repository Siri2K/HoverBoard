#ifndef INFRARED_H
#define INFRARED_H

// Include Libraries
#include "adc.h"
#include "uart.h"
#include <stdlib.h>

// Define IR pins
#define IR_PIN PC0

// Declare Functions
void IR_init(); // Intialize Infrared
float IR_getVoltage(); // Obtain IR Voltage
int IR_getDistance(float voltage); // Obtain IR Distances

#endif