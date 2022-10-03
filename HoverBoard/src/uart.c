#include "uart.h"

// Define UART Parameters
#define F_CPU 16000000UL
#define BAUD 9600UL
#define UBRR (F_CPU/(BAUD*16UL)-1)

// Define Buffers
static volatile uint8_t TX_buffer1[10] , TX_buffer2[10];
static const char CRLF[3] = {13,10};

// Define Functions
void uart_init()
{
    UBRR0H = (uint8_t) (UBRR>>8); // Set UART Upper Portion
    UBRR0L = (uint8_t) (UBRR);
    UCSR0B = (1<<TXCIE0) | (1<<TXEN0); // Enable TX and TX IRQ
}

void sendByte(uint8_t str)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
    flags.TX_finished = 0;
    UDR0 = str;
}

ISR(USART_TX_vect)
{
    uint8_t* msg;
    msg++;

    if(*msg)
    {
        UDR0 = msg;
    }
    else
    {
        flags.TX_finished = 1;
    }
}

void sendString(uint8_t* str)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
    uint8_t* msg = str;
    uint8_t i = 0;
    
    // Loop Through Each character in string
    while(msg[i] != NULL)
    {
        sendByte(msg[i]);
        i++;
    }
    flags.TX_finished = 0;
}

/*
uint8_t* toString(int number)
{
    char* msg;
    msg = sprintf(msg,"%d", number);
    uint8_t* str = (uint8_t*)msg;
    return str;
}
*/

void sendInt(int16_t data, uint8_t base, uint8_t crlf)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
    flags.TX_finished = 0;
    itoa(data, (char*)&TX_buffer1[0], base);

    if(crlf)
    {
        strcat(TX_buffer1,CRLF);
    }

    uint8_t* msg = TX_buffer1;
    UDR0 = *msg;
}