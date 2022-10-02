// Include Libraries and Headers
#include "infrared.h"

int main()
{
    // Initialize Modules
    sei(); // Setup General Interrupt
    uart_init(); // Initalize UART
    adc_init(7,1); // Initialize ADC
    

    // Test UART
    send_string((uint8_t*)"UART is Working\n");
    send_int(10);

    // Test Infrared
    uint8_t* ADC_ptr = IR_get_distance();

    for(uint16_t i = 0; i<6; i++)
    {
        send_int(*ADC_ptr);
        ADC_ptr++;
    }

    return 0;
}