// Include Libraries
extern "C"
{
    #include "uart.h"
    #include "adc.h"
    #include "infrared.h"
    #include "ultrasonic.h"
    #include <util/delay.h>
}

// Define LED Pins
#define D3_LED PD3
#define YELLOW_LED PB5

// Sensor Choice
#define sensor_choice 1 // 1: IR range Finder , 2: US sensor

// Intialize GPIO's
void GPIO_init()
{
    cli(); // Stop Intterupts
    DDRB |= (1<<YELLOW_LED); // Initialize LED pins
    DDRD |= (1<<D3_LED);
    sei(); // Start General Interupts
}

// Setup Brightness of LED based on distance
int LEDBright(int distance)
{
    // Default Brightness
    int brightness = 0;
    PORTB &= ~((1<<D3_LED) | (1<<YELLOW_LED)); // Turn off both LED's

    // Determine Brightness based on Distance
    if(distance < 15)
    {
        brightness = 255;
        PORTB |= (1<<YELLOW_LED); // Turn on Out_of_range LED
        
    }
    else if (distance > 40)
    {
        brightness = 0;
        PORTB |= (1<<YELLOW_LED); // Turn on Out_of_range LED
    }
    else
    {
        brightness = 255*(40-distance)/(40-15);
        PORTB &= (1<<YELLOW_LED); // Turn off Out_of_range LED
        LED_PWM(brightness); 
    }

    return brightness;
}

void LED_PWM(int brightness)
{
    double time = brightness/255*1000; // Determine LED on time

    // Turn LED on for a second
    PORTB |= (1<<D3_LED);
    delay_ms(time);
    PORTB &= ~(1<<D3_LED);
    delay_ms(1000-time);

}

// Setup Variable Delays
void delay_ms(uint16_t count)
{
    for(int i = 0; i<count; i++)
    {
        _delay_ms(1);
    }
}

void delay_us(uint16_t count)
{
    for(int i = 0; i<count; i++)
    {
        _delay_us(1);
    }
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
    
    // Run based on Sensor
    switch(sensor_choice)
    {
        case 1: // IR Sensor
        {
            //Intialize Infrared
            IR_init();

            // Display Data
            while(true)
            {
                // Send ADC Value
                sendString((uint8_t*)"ADC = ");
                sendInt(IR_getADC());

                // Send Distance
                sendString((uint8_t*)"Distance (in cm) = ");
                sendInt(IR_getDistance());

                // Add Space from Previous Reading
                sendString((uint8_t*)"\n\n");
            }
            break;
        }

        case 2: // US Sensor
        {
            //Intialize Infrared
            US_init();

            // Display Data
            while(true)
            {
                // Cycle Trigger Pulse
                trigger();
                _delay_us(11);

                // Send Pulse  Value
                sendString((uint8_t*)"Pulse = ");
                sendInt(US_getPulse());

                // Send Distance
                sendString((uint8_t*)"Distance (in cm) = ");
                sendInt(US_getDistance());

                // Add Space from Previous Reading
                sendString((uint8_t*)"\n\n");
            }
            break;
        }
        default: // Not the Part of Choice
        {
            sendString((uint8_t*)"Sensor not Chosen");
        }
    }
    
    return 0;
}