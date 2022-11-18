#ifndef UART_H
#define UART_H

// Include Libraries and Headers
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

// Include Global Variable
static volatile uint8_t* msg;

// Define UART Parameters
#define F_CPU 16000000UL
#define BAUD 9600UL
#define UBRR (F_CPU/((BAUD)*(16UL))-1)

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
void sendInt(int16_t data); // Send Number to UART

#endif