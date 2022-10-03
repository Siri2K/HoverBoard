#include "infrared.h"


void IR_init()
{
    DDRC &= ~(1<<IR_pin);
}

float IR_getVoltage()
{
    return readADC(IR_pin) * 5/1023;
}

int IR_getDistance(float voltage)
{
    return 29.988*pow(voltage,-1.173);
}