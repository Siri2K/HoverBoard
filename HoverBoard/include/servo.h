#ifndef SERVO_H
#define SERVO_H

// Define Servo Pin
#define SERVO_PIN PB1
#define FREQUENCY 20000 //In ms (leave last 3 0s)

// Include Libraires
#include <util/delay.h>
#include <avr/io.h>

void Servo_Init();
void Move_Servo(int16_t val);

#endif

