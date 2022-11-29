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

float IR_getVoltage(int IR_Num)
{
  uint16_t* IR_ADC = IR_getADC();
  float voltage;

  switch(IR_Num)
  {
    case 0 :
      voltage = IR_ADC[0] * (5.0/1023.0);
      break;
    case 1 :
      voltage = IR_ADC[1] * (5.0/1023.0);
      break;

    case 2 :
      voltage = IR_ADC[2] * (5.0/1023.0);
      break;

    default:
      voltage = IR_ADC[0] * (5.0/1023.0);
      break;
  }

  return voltage;
}

int IR_getDistance(int IR_Num)
{
  return 29.988*(pow(IR_getVoltage(IR_Num),-1.173));
}