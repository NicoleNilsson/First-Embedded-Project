#include <avr/io.h>

#ifndef __SERIAL_H
#define __SERIAL_H

void uart_init();
void uart_put_char(unsigned char data);
char uart_get_char(void);
void uart_put_str(const char *str);
void uart_rec_str(char *buffer, uint8_t maxLength);
void uart_echo_char();
void uart_echo_str();

#endif