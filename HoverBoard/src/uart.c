#include "uart.h"

// Define Variables
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR (F_CPU/(BAUD*16UL) -1)

void uart_init()
{
    UBRR0H = (uint8_t) (UBRR>>8);
    UBRR0L = (uint8_t) UBRR;
    
    // Enable TX and RX 
    UCSR0B |= (1<<TXCIE0) | (1<<TXEN0); // Enable TX and TX IRQ
    UCSR0B |= (1<<RXCIE0) | (1<<RXEN0); // Enable TX and TX IRQ
    UCSR0C = (3<<UCSZ00); // Asynchronous UART
}

ISR(USART_TX_vect)
{
    uint8_t *msg;
    msg++; //unmute ur self 

    if(*msg)
    {
        UDR0 = *msg;
    }
    else
    {
        flags.TX_finished = 1;
    }
}


void send_byte(uint8_t str)
{
    while(!flags.TX_finished);
    flags.TX_finished = 0;
    UDR0 = str;
}


void send_int(int16_t data, uint8_t base, uint8_t crlf)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
    flags.TX_finished = 0;
    itoa(data, (char*)&TXbuffer1[0], base);

    if(crlf)
    {
        strcat(TXbuffer1, CRLF);
    }
    uint8_t *msg;
    msg = TXbuffer1;
    UDR0 = *msg;
}

void send_reading(int16_t data, char label[], uint8_t crlf)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
    flags.TX_finished = 0;

    strcpy(TXbuffer1,label);
    itoa(data, (char*)&TXbuffer2[0], 10);
    strcat(TXbuffer1, TXbuffer2);

    if(crlf)
    {
        strcat(TXbuffer1, CRLF);
    }
    uint8_t *msg;
    msg = TXbuffer1;
    UDR0 = *msg;
}

void send_string(uint8_t* str)
{
    while(!flags.TX_finished); // Wait for Other Transmission to Finish
    uint8_t *msg;
    msg = str;

    uint16_t i = 0;
    do
    {
        UDR0 = msg[i];
		i++;

    } while(str[i] != '\0');

    UDR0 = *msg;
    flags.TX_finished = 0;
}