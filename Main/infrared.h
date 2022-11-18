#ifndef INFRARED_H
#define INFRARED_H

// Include Libraries
#include "adc.h"
#include "uart.h"
#include <stdlib.h>

// Define IR pins
#define IR1_PIN PC0
#define IR2_PIN PC1
#define IR3_PIN PC2

// Declare Functions
void IR_init(); // Intialize Infrared
uint16_t* IR_getADC(); // Get ADC reading 
float* IR_getVoltage(); // Obtain IR Voltage
int* IR_getDistance(); // Obtain IR Distances

#endif