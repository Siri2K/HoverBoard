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
#define YELLOW_LED PB5

// Intialize GPIO's
void GPIO_init()
{
    DDRB = (1<<YELLOW_LED); // Initialize LED pins
    DDRD = (1<<D3_LED);
    IR_init();
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
    sei(); // Enable Global Intterupt
    GPIO_init();
    uart_init(); // Initialize UART
    adc_init(); // Intialize ADC

    //Test UART
    flags.TX_finished = 1;
    sendString((uint8_t*)"UART Deployed \n");
    
    // Get IR distance
    uint16_t ADC_val = 0; // ADC_val
    int distance = 0; // Distance from Sensor
    int brightness = 0; // LED Brightness

    while(true)
    {
        ADC_val = readADC(IR_PIN); // Get IR ADC
        distance = IR_getDistance(IR_getVoltage()); // GET Distance from Sensor
        brightness = LEDBright(distance); // Determine LED Brightness

        // Display ADC_val to UART
        sendString((uint8_t*)"ADC = ");
        sendInt(ADC_val);
        sendString((uint8_t*)"\n");

        // Display Distance to UART
        sendString((uint8_t*)"Distance = ");
        sendInt(distance);
        sendString((uint8_t*)"cm\n");

        // Next Scan
        sendString((uint8_t*)"\n");
    }
    

    return 0;
}