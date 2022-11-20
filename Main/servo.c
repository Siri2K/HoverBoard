#include "servo.h"

void SERVO_init()
{
  // initalize Pin
  DDRB |= (1<<SERVO);
  
  // Configure Timer 1
  TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
  TCCR1A |= (1<<WGM10);
  ICR1 = 19999; // Set FPWM = 50Hz (Period 20ms)
  TCCR1B |= ((1<<CS11)|(1<<CS10));
}

void SERVO_turn(int16_t angle)
{  
  OCR1A = 600+10*angle;
  _delay_ms(15);
}