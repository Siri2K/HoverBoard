// Call All Libraries
extern "C"
{
  // Component Header
  #include "adc.h"
  #include "infrared.h"
  #include "fan.h"
  #include "uart.h"
}
#include <Servo.h>

// Define Pin
#define ServoMotor 9 // Servo Motor at PB1
Servo myServo;

// Setup Inital Values
static int init_angle = 90;
static int distanceMid;

// Setup Motor Positions
static int drive_fan_min = 150;
static int lift_fan_min = 200;
static int fan_max = 240;
static int fwd = 0;
static int left = 85;
static int right = -85;

// Functions for Servo Motor
void SERVO_init()
{
	myServo.attach(ServoMotor,600,2400); // PB1 set to Output

}

void moveServoRight(int angle) //0 to +90
{
	// Move Servo Motor
	for(int i = init_angle; i<=angle; i++)
	{
		myServo.write(i);  // tell servo to go to position in variable 'pos'
		delay(15);
	}
}

void moveServoLeft(int angle) // -90 to 0
{
	// Move Servo Motor
	for(int i = init_angle; i>=angle; i--)
	{
		myServo.write(i);  // tell servo to go to position in variable 'pos'
		delay(15);
	}
}

void controlServo(float angle) // Move Servo Motor based on IMU
{
	angle = angle + 90;
	if(angle >= 90 && angle <180)
	{
		if(angle>init_angle)
		{
			moveServoRight(angle);
		}
		else
		{
			moveServoLeft(angle);
		}
		init_angle = angle;
	}
	else if(angle > 0 && angle <90)
	{
		if(angle<init_angle)
		{
			moveServoLeft(angle);
		}
		else
		{
			moveServoRight(angle);
		}
		init_angle = angle;
	}
	
}

// Initialize Components
void GPIO_init()
{
  FAN_init(); // Intialize Fan
  IR_init(); // Intialize IR
  SERVO_init(); // Intialize Servo
}

void obstacle_avoid()
{
  // Initialize Readings
  int distanceR = 0;
  int distanceL = 0;
  distanceMid = IR_getDistance(0);
  _delay_ms(100);


  // Avoid Based On Readings
  if(distanceMid < 40)
  {
    
    // Read Right and Left Sensor
    distanceR = IR_getDistance(1);
    _delay_ms(100);

    distanceL = IR_getDistance(2);
    _delay_ms(100);

    // Slow Down HoverBoard
    distanceMid = IR_getDistance(0);
    _delay_ms(100);

    if(distanceR > 40 && distanceMid < 40)
    {
      // Slow Down HoverBoard
      DRIVE_FAN_pwr(25);
     _delay_ms(100);

      controlServo(right);
      _delay_ms(2500);

      controlServo(fwd);
      _delay_ms(100);
    }
    else if(distanceL > 40 && distanceMid<40)
    {
      // Slow Down HoverBoard
      DRIVE_FAN_pwr(100);
     _delay_ms(100);

      controlServo(left);
      _delay_ms(2500);

      controlServo(fwd);
      _delay_ms(100);
    }
    else
    {
      controlServo(10);
      _delay_ms(100);

      // Slow Down HoverBoard
      distanceMid = IR_getDistance(0);
      _delay_ms(100);
    }

  }
  else
  {
    // Slow Down HoverBoard
    distanceMid = IR_getDistance(0);
    _delay_ms(100);
    
    DRIVE_FAN_pwr(200);
    delay(100);
  }
}

void start_hover()
{
  // Initialize Servo Motor
  controlServo(fwd);
  _delay_ms(500);

  // Set Drive Fan To no Power
  DRIVE_FAN_pwr(0);
  _delay_ms(100);

  // Lift Fan Upwards
  LIFT_FAN_pwr(fan_max);
  _delay_ms(500);

  // Reduce Lift Fan Power
  LIFT_FAN_pwr(lift_fan_min);
  _delay_ms(1000);

}

void setup()
{
  // Initialize Sensors
  GPIO_init();
  adc_init(); // Intialize ADC

  // Start Hovering
  start_hover();
}


void loop() 
{
  // Move a Straight Line
  DRIVE_FAN_pwr(drive_fan_min);
  _delay_ms(100);
}

