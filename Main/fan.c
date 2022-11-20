#include "fan.h"

void FAN_init()
{
  // Initalize Pins
  DDRD |= (1<<LIFT_FAN) | (1<<DRIVE_FAN);

  // Set PD6 to PWM
  TCCR0A |= (1<<COM0A1)|(1<<COM0B1);
  TCCR0A |= (1<<WGM00);
  OCR0A = 0;
  TCCR0B |= ((1<<CS01)|(1<<CS00));  
}

void DRIVE_FAN_PWR(int16_t power)
{
  OCR0A = power;
}

void LIFT_FAN_PWR(bool fan_status)
{
  if(fan_status == true)
  {
    PORTD |= (1<<LIFT_FAN);
  }
  else
  {
    PORTD &= ~(1<<LIFT_FAN);
  }
}