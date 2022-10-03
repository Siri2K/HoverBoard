#ifndef UART_H
#define UART_H

// Include Libraries and Headers
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

// Include Global Variable
static volatile uint8_t* msg;

// Define Structures
volatile struct
{
    uint8_t TX_finished : 1;
    uint8_t sample : 1;
    uint8_t mode : 1;
    uint8_t stop : 1;

    uint8_t T1_ovf0 : 2;
    uint8_t T1_ovf1 : 2;
} flags;

// Setup Functions
void uart_init(); // Initialize UART
void sendByte(uint8_t str); // Send Byte to UART
ISR(USART_TX_vect); // Transmit Byte
void sendString(uint8_t* str); // Send String to UART
uint8_t* toString(int number); // Convert Number to String
void sendInt(int16_t data, uint8_t base, uint8_t crlf); // Send Number to UART


#endif