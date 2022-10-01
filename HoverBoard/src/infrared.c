#include "infrared.h"

// Define Functions
void IR_init()
{
    DDRC &= ~(1<<PC0);
}

uint16_t IR_get_distance()
{
    return (PINC & (1<<PC0)); // Read Attached Infrared
}