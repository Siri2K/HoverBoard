#include "infrared.h"

// Define Pins
#define IR_SIG (1<<PC0)

void IR_init()
{
    DDRC &= ~IR_SIG;
}

uint8_t* IR_get_distance()
{
    return &ADC_data.ADC0;
}