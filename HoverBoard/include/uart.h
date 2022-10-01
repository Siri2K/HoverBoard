#ifndef UART_H
#define UART_H

// Include Liraries and Headers
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

// Declare Variables
static const char CRLF[3]={13,10};
static volatile uint8_t TXbuffer1[10],TXbuffer2[10];

// Setup Structures
volatile struct
{
    uint8_t TX_finished : 1;
    uint8_t sample : 1;
    uint8_t mode : 1;
    uint8_t stop : 1;
    uint8_t T1_ovf0 : 2;
    uint8_t T1_ovf1 : 2;

} flags;

// Define Functions
void uart_init();
ISR(USART_TX_vect);
void send_int(int16_t data, uint8_t base, uint8_t crlf);
void send_reading(int16_t data, char label[], uint8_t crlf);
void send_string(uint8_t* str);
void send_byte(uint8_t str);

#endif 