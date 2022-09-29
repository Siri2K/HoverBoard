#include "uart.h"


#define BAUD 9600UL
#define UBRR ((F_CPU)/((BAUD*16UL) -1))

void UART_init()
{
    UBRR0H = (uint8_t)(UBRR>>8); // Sert UART Speed as defined by UBRR
    UBRR0L = (uint8_t)UBRR;
    UCSR0B |= (1<<TXCIE0) | (1<<TXEN0)|(1<<RXCIE0) | (1<<RXEN0) ; // Enable RX, TX, RX IRQ and TX IRQ
    UCSR0C = (3<<UCSZ00); // ASynchronous UART
}