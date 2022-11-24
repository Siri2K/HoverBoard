#include "infrared.h"


void IR_init()
{
    DDRC = 0x00;
}

uint16_t* IR_getADC()
{
    static uint16_t IR_ADC[3];

    // Store ADC file
    IR_ADC[0] = readADC(IR_PIN1);
    IR_ADC[1] = readADC(IR_PIN2);
    IR_ADC[2] = readADC(IR_PIN3);
    
    return IR_ADC;
}

float* IR_getVoltage()
{
  uint16_t* IR_ADC = IR_getADC();
  static float IR_voltage[3];

  IR_voltage[0] = IR_ADC[0] * (5.0/1023.0);
  IR_voltage[1] = IR_ADC[1] * (5.0/1023.0);
  IR_voltage[2] = IR_ADC[2] * (5.0/1023.0);

  return IR_voltage;
}

int* IR_getDistance()
{
  float* IR_volt = IR_getVoltage();
  static int IR_distance[3];

  IR_distance[0] = 29.988*(pow(IR_volt[0],-1.173));
  IR_distance[1] = 29.988*(pow(IR_volt[1],-1.173));
  IR_distance[2] = 29.988*(pow(IR_volt[2],-1.173));

  return IR_distance;
}