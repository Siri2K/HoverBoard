// Include Library and Headers
#include "uart.h"
#include "ultrasonic.h"
#include "infrared.h"
#include <util/delay.h>


int main()
{
    // Initialize UART
    uart_init();
    flags.TX_finished = 1; 

    // Initialize Sensors
    ultrasonic_init();
    IR_init(); 

    // Read String to Confirm UART is working
    uint8_t str[] = "Testing UART, Testing UART";
    send_string(str);

    while(true)
    {
        // Use the Ultrasonic Sensor
        trigger();
        _delay_us(10);

        // Ultrasonic Sensor Reading
        send_reading(pulse_data.pulse0, (char*) pulse_data.pulse0, flags.TX_finished);

        // Read from Infrared Sensor
         send_reading(IR_get_distance(), (char*) pulse_data.pulse1, flags.TX_finished);

    }

    return 0;
}