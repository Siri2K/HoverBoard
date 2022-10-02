// Include Library and Headers
#include "adc.h"
#include "uart.h"
#include "ultrasonic.h"
#include "infrared.h"
#include <util/delay.h>


int main()
{
    // Setup General Interrupt
	sei();
	
	// Initialize ADC
	adc_init(0,1);
	
	// Initialize UART
	uart_init();
    flags.TX_finished = 1;

    // Initialize Sensors
    ultrasonic_init();
    IR_init(); 

    // Read String to Confirm UART is working
    send_string("Testing UART \n");

    // Character Variables
    char show_a[16];

    while(true)
    {
        // Use the Ultrasonic Sensor
        trigger();
        _delay_us(10);

        // Use the ADC
        uint8_t *ADC_ptr = &ADC_data.ADC0;
        
        for(uint8_t i = 1; i<2; i++)
        {
            if(i = 1)
            {
                uint8_t jmax = 1;
                char label[] = "IR ";
                ADC_data.ADC0 = adc_IR(pulse_data.pulse0,jmax); 

            }
            else
            {
                uint8_t jmax = 4;
                char label[] = "US ";
                ADC_data.ADC0 = adc_US(pulse_data.pulse0/58); 
            }

            for(uint8_t j = 0; j<jmax; j++)
            {
                send_reading(*ADC_ptr, label + "Distance = " , 1);
            }
        }
    }

    return 0;
}