#include <avr/io.h>

#ifndef __SERIAL_H
#define __SERIAL_H

#define HAS_RECIEVED_CHAR (UCSR0A & (1 << RXC0))
#define REGISTER_EMPTY (UCSR0A & (1 << UDRE0))

void uart_initiate();
void uart_transmit_char(unsigned char data);
char uart_recieve_char(void);
void uart_transmit_str(const char *str);
void uart_recieve_str(char* buffer, uint8_t maxLength);
void uart_echo_char();
//void uart_echo_str(char *str);

#endif