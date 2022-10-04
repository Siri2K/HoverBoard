#include "infrared.h"


void IR_init()
{
    DDRC = 0x00;
}

float IR_getVoltage()
{
    return readADC(IR_PIN) * (5.0/1023.0);
}

int IR_getDistance(float voltage)
{
    return 29.988*(pow(voltage,-1.173));
}