// Call All Libraries
extern "C"
{
  // Component Header
  #include "adc.h"
  #include "infrared.h"
  #include "fan.h"
}
#include <Servo.h>

// Define Pin
#define ServoMotor 9 // Servo Motor at PB1
Servo myServo;

// Setup Inital Angle
static int init_angle;


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
}

// Get Sensor Detection Flags
bool* IR_flag(int* IR_dist)
{
  // Define variables
  bool flag[3] = {false,false,false};
  int distance[3];

  // Convert distances to array
  for(int i=0;i<3;i++)
  {
    distance[i] = IR_dist[i];

    // Setup Flag
    if(distance[i]>15 && distance[i]<40)
    {
      flag[i] = true;
    }
    else
    {
      flag[i] = false;
    }
  } 
}

void obstace_avoid(int* IR_dist)
{
  // Get IR flags
  bool* IR_Flag = IR_flag(IR_dist);
  bool obstacle_flag[3];
  
  // Convert distances to array
  for(int i=0;i<3;i++)
  {
    obstacle_flag[i] = IR_flag[i];
  }

  // Setup Obstacle Avoidance
  if(obstacle_flag[0])
  {
    // Reduce Speed at wall ahead
    DRIVE_FAN_pwr(100);
    delay(15);

    if(!obstacle_flag[1] && obstacle_flag[2]) // Turn Right at opening 
    {
      // Make a Right turn
      controlServo(85);
      delay(2500);

      // Go back to Straight turn
      controlServo(0);
      delay(15);
    }
    else if(!obstacle_flag[2] && obstacle_flag[1]) // Turn Left at opening
    {
      // Make a Right turn
      controlServo(-85);
      delay(2500);

      // Go back to Straight turn
      controlServo(0);
      delay(15);
    }
    else
    {
      controlServo(0);
      delay(15);
    }
  } 
  else
  {
    controlServo(0); // Middle
    DRIVE_FAN_pwr(255); // Max Speed
    delay(15);
  }
}


void setup()
{
  // Initialize Sensors
  GPIO_init();
  adc_init(); // Intialize ADC

  // INitialize Fan
  LIFT_FAN_pwr(true);
  delay(3000);

}

void loop() 
{
  obstace_avoid(IR_getDistance());
}

