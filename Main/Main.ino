// Call All Libraries
extern "C"
{
  // Component Header
  #include "uart.h"
  #include "adc.h"
  #include "infrared.h"
}

// Initialize Components
void GPIO_init()
{
  cli(); // Disable General Intterupt
  IR_init(); // Intialize IR
  sei(); // Enable General Intterupt
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

  // Test IR Sensors
  IR_init();

  while(true)
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

  return 0;
}
