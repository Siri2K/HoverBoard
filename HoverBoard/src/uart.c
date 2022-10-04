#include "uart.h"

// Define Buffers
static const char CRLF[3] = {13,10};

// Define Functions
void uart_init()
{
    UBRR0H = (uint8_t) (UBRR>>8); // Set UART Upper Portion
    UBRR0L = (uint8_t) (UBRR);
    UCSR0B |= (1<<TXCIE0) | (1<<TXEN0); // Enable TX and TX IRQ
    UCSR0C = (3<<UCSZ00);
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


void sendInt(int16_t data)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
   
    uint8_t crlf = 1;
    uint8_t TX_buffer[10];
    itoa(data, (char*)&TX_buffer[0], 10);

    if(crlf)
    {
        strcat(TX_buffer,CRLF);
    }

    uint8_t* msg = TX_buffer;
    uint8_t i = 0;

    // Loop Through Each character in string
    while(msg[i] != NULL)
    {
        sendByte(msg[i]);
        i++;
    }
    flags.TX_finished = 0;
}