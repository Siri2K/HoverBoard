// Call All Libraries
extern "C"
{
  // Component Header
  #include "uart.h"
  #include "adc.h"
  #include "infrared.h"
  #include "fan.h"
}

// Initialize Components
void GPIO_init()
{
  cli(); // Disable General Intterupt
  FAN_init();
  IR_init(); // Intialize IR
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
  LIFT_FAN_PWR(true);

  // Check Drive Fan
  DRIVE_FAN_PWR(15);
  DRIVE_FAN_PWR(165);  
  DRIVE_FAN_PWR(240);  
  DRIVE_FAN_PWR(150);  
  DRIVE_FAN_PWR(0);    

  LIFT_FAN_PWR(false);
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
    for(int i = 0; i<1;i++)
    {
      for(int j = 1; j<100;j++)      
      {
        switch (i)
        {
          case 0:
            TEST_IR();          
            break;
          case 1:
            TEST_FAN();
            break;
          default:
            break;          
        }
      }    
    }
  }

  return 0;
}
