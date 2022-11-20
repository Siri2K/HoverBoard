// Call All Libraries
extern "C"
{
  // Component Header
  #include "uart.h"
  #include "adc.h"
  #include "infrared.h"
  #include "fan.h"
  #include "servo.h"
}

// Initialize Components
void GPIO_init()
{
  cli(); // Disable General Intterupt
  FAN_init(); // Intialize Fan
  IR_init(); // Intialize IR
  SERVO_init(); // Initialize Servo Motor
  sei(); // Enable General Intterupt
}

void TEST_IR()
{
  // Get IR sensor distances
    int*IR_Distance = IR_getDistance();    
    int distance[3];
    for(int i = 0; i<3;i++)
    {
      distance[i] = *IR_Distance;
    }

    // Display Distances to UART
    sendString((uint8_t*)"IR_C0 Distance (in cm) : ");
    sendInt(distance[0]); 
    sendString((uint8_t*) "\n");

    sendString((uint8_t*)"IR_C1 Distance (in cm) : ");
    sendInt(distance[1]); 
    sendString((uint8_t*) "\n");

    sendString((uint8_t*)"IR_C2 Distance (in cm) : ");
    sendInt(distance[2]); 
    sendString((uint8_t*) "\n");  
}

void TEST_FAN()
{
  LIFT_FAN_pwr(true);

  // Check Drive Fan
  DRIVE_FAN_pwr(15);
  DRIVE_FAN_pwr(165);  
  DRIVE_FAN_pwr(240);
  DRIVE_FAN_pwr(150);    
  DRIVE_FAN_pwr(0);

  // Turn Off Fan
  LIFT_FAN_pwr(false);
}

void TEST_SERVO()
{
  // Start Direction
  SERVO_turn(90);

  // Go Between Left And Right
  SERVO_turn(0);
  SERVO_turn(180);
  SERVO_turn(45);
  SERVO_turn(135);

  // End Direction
  SERVO_turn(90);

}

// Run Loop
int main()
{
  // Initialize All components
  GPIO_init();
  uart_init(); // Initialize UART
  adc_init(); // Intialize ADC

  // Test UART 
  flags.TX_finished = 1;
  sendString((uint8_t*)"UART Deployed \n");


  while(true)
  {
    // Test Sensor    
    for(int i = 1; i<100; i++)
    {
      TEST_IR(); 
    }
    //Test Fan and Servo Motor
    TEST_FAN();
    TEST_SERVO();  
  }

  return 0;
}
