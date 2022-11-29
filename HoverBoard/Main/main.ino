// Include Libraries
extern "C"
{
    #include "uart.h"
    #include "adc.h"
    #include "led.h"
    #include "infrared.h"
    #include "ultrasonic.h"
    #include <util/delay.h>
}

// Define LED Pins
#define D3_LED PB3
#define YELLOW_LED PB5

// Sensor Choice
#define sensor_choice 1 // 1: IR range Finder , 2: US sensor

// Intialize LED's
void GPIO_init()
{
    cli(); // turn Off Genral Intterupt

    // Initialize Ports
    LED_Init(); // Initalize LED's
    IR_init(); // Intialize IR
    // US_init(); // Initalize US

    // Enable Intterupts
    sei();

}

int main()
{
    // Intialize All components
    GPIO_init();
    uart_init(); // Initialize UART
    adc_init(); // Intialize ADC

    //Test UART
    flags.TX_finished = 1;
    sendString((uint8_t*)"UART Deployed \n");

    switch(sensor_choice)
    {
        case 1: // Infrared Choice
        {
            // Intialize Infrared
            IR_init();

            // Get & Send Data to UART
            while(true)
            {
                
                // Store Data in UART
                sendString((uint8_t*)"ADC : ");
                sendInt(IR_getADC());

                sendString((uint8_t*)"Distane (in cm) : ");
                sendInt(IR_getDistance());

                // Space Between Each Result
                sendString((uint8_t*)"\n\n");

                // Display LED Changes
                LED_Brightness(IR_getDistance());

            }
        }

        case 2: // Ultrasonic Sensor Choice
        {
            // Store Data in UART
            sendString((uint8_t*)"Pulse : ");
            sendInt(US_getPulse());

            sendString((uint8_t*)"Distane (in cm) : ");
            sendInt(US_getDistance());

            // Space Between Each Result
            sendString((uint8_t*)"\n\n");

            // Display LED Changes
            LED_Brightness(US_getDistance());
            _delay_ms(50);

        }

        default:
        {
            sendString((uint8_t*)"Sensor Not Chosen \n");
        }
    }

    return 0;
}