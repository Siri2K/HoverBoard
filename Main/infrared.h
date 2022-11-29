#ifndef INFRARED_H
#define INFRARED_H

// Include Libraries
#include "adc.h"
#include <stdlib.h>

// Define IR pins
#define IR_PIN1 PC0
#define IR_PIN2 PC1
#define IR_PIN3 PC2

// Declare Functions
void IR_init(); // Intialize Infrared
uint16_t* IR_getADC(); // Get ADC reading 
float IR_getVoltage(int IR_Num); // Obtain IR Voltage
int IR_getDistance(int IR_Num); // Obtain IR Distances

#endif