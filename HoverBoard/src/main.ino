// Include Libraries
extern "C"
{
    #include "uart.h"
    #include "adc.h"
    #include "infrared.h"
    #include <util/delay.h>
}

// Define LED Pins
#define D3_LED PD3
#define Yellow_LED PB5


// Intialize GPIO's
void GPIO_init()
{
    DDRB = (1<<Yellow_LED); // Initialize LED pins
    DDRD = (1<<D3_LED);
    IR_init();
}

// Setup Brightness of LED based on distance
int LEDBright(int distance)
{
    // Default Brightness
    int brightness = 0;
    PORTB &= ~((1<<D3_LED) | (1<<Yellow_LED)); // Turn off both LED's

    // Determine Brightness based on Distance
    if(distance < 15)
    {
        brightness = 255;
        PORTB |= (1<<Yellow_LED); // Turn on Out_of_range LED
        
    }
    else if (distance > 40)
    {
        brightness = 0;
        PORTB |= (1<<Yellow_LED); // Turn on Out_of_range LED
    }
    else
    {
        brightness = 255*(40-distance)/(40-15);
        PORTB &= (1<<Yellow_LED); // Turn off Out_of_range LED
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
    sei(); // Enable Global Intterupt
    GPIO_init();
    uart_init(); // Initialize UART
    adc_init(); // Intialize ADC

    //Test UART
    flags.TX_finished = 1;
    sendString((uint8_t*)"UART Deployed with number : ");
    sendInt(123456789,10,1);
    sendString((uint8_t*)"\n");

    // Get IR distance
    int distance = 0;
    int brightness = 0;
    while(true)
    {
        distance = IR_getDistance(IR_getVoltage());
        brightness = LEDBright(distance);

        // Display Distance to UART
        sendString((uint8_t*)"Distance = ");
        sendInt(distance,10,1);
        sendString((uint8_t*)"\n");

        // Display ADC to UART
        sendString((uint8_t*)"Brightness = ");
        sendInt(brightness,10,1);
        sendString((uint8_t*)"\n");

        // Next Scan
        sendString((uint8_t*)"\n");
    }

    return 0;
}