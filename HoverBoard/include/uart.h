#ifndef UART_H
#define UART_H

// Include Libraries and Other Headers
//#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

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


/*Define Functions*/
// Setup UART
void uart_init(); // Intiialize UART Serial Module
ISR(USART_TX_vect); //Transmit Vector

// Convert and Send data to UART
uint8_t* toString(uint8_t number);
void send_byte(uint8_t byte); // Send Byte to UART
void send_int(uint8_t number); // Send Integer to UART
void send_string(uint8_t* str); // Send String to UART

#endif