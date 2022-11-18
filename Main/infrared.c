#include "infrared.h"

void IR_init()
{
  DDRC = 0x00; // Keep PORT C as inputs
}

uint16_t* IR_getADC()
{
  uint16_t  adc_reading[3];

  // Read ADC from each Infrared
  adc_reading[0] = readADC(IR1_PIN);
  adc_reading[1] = readADC(IR2_PIN);
  adc_reading[2] = readADC(IR3_PIN);

  return adc_reading;
}

float* IR_getVoltage()
{
  uint16_t* IR_readings; 
  float voltage_reading[3];  

  // Convert ADC readings to Voltages
  IR_readings = IR_getADC();
  for(int i = 0; i<3;i++)
  {
    voltage_reading[i] = (*IR_readings)*(5.0/1023.0);
  }

  return voltage_reading;
}

int* IR_getDistance()
{
  float* voltage_reading;   
  int obstacle_distance[3];

  //Convert Voltage Readings to Distance
  voltage_reading = IR_getVoltage();
  for(int i = 0; i<3; i++)
  {
    obstacle_distance[i] = 29.988*(pow(*voltage_reading,-1.173));
  }
  
  return obstacle_distance;
}