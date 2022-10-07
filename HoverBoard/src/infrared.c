#include "infrared.h"


void IR_init()
{
    DDRC = 0x00;
}

uint16_t IR_getADC()
{
    return readADC(IR_PIN);
}

float IR_getVoltage()
{
    return IR_getADC() * (5.0/1023.0);
}

int IR_getDistance()
{
    return 29.988*(pow(IR_getVoltage(),-1.173));
}