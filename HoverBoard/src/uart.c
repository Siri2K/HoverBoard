#include "uart.h"

// Define Serial Variables
#define F_CPU 16000000UL
#define baud 9600
#define UBRR (F_CPU/(baud*16UL)-1)


void uart_init()
{
    UBRR0H = (uint8_t)(UBRR>8);
    UBRR0L = (uint8_t)UBRR;
    UCSR0B = 0x48; //UCSR0B = 0100 1000  ->ENABLE TX and TX IRQ
    UCSR0C = (3<<UCSZ00); // Asyncronous UART 8-N-1
}

ISR(USART_TX_vect)
{
    uint8_t* msg;
    msg++;

    if(*msg)
    {
        UDR0 = *msg;
    }
    else
    {
        flags.TX_finished = 1;
    }
}

uint8_t* toString(uint8_t number)
{
    int n = log10(number)+1;
    uint8_t* str = calloc(number, sizeof(char));

    // Store Each Digit to String
    for(int i = n-1; i>=0; i--, number/10)
    {
        str[i] = (number%10) + '0';
    }

    return str;
}

void send_byte(uint8_t byte)
{
    while(!flags.TX_finished); // Wait till Previous Message is fully transmitted
    flags.TX_finished = 0;
    UDR0 = byte;
}

void send_int(uint8_t number)
{
    while(!flags.TX_finished);
    
    // Convert & Send to UART as String
    uint8_t* msg = toString(number);
    send_string(msg);
    flags.TX_finished = 0;
}

void send_string(uint8_t* str)
{
    while(!flags.TX_finished);
    uint8_t* msg = str;
    uint16_t i = 0;

    // Send Each byte to UART
    do
    {
        send_byte(msg[i]);

    }while(msg[i] != NULL);

    send_byte('\n');
    flags.TX_finished = 0;
}