#ifndef LED_H
#define LED_H

// Define Libraries
#include "adc.h"
#include "uart.h"

// Define LED Pins
#define D3_LED PB3
#define YELLOW_LED PB5

// Define Functions
void LED_Init(); // Initalize LED
void LED_Brightness(int16_t distance); // Setup Brighness


#endif