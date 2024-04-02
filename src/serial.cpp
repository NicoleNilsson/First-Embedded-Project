#include <avr/io.h>
#include "button.h"

#define SERIAL_8N1 0x06

void uart_initiate(){
  //baud rate=9600, frameformat=8N1
  uint16_t baudRate = 9600;
  uint16_t baudSetting = (F_CPU / 4 / baudRate - 1) / 2;
  UCSR0A = 1 << U2X0; //double speed mode
  // assign the baudSetting , a.k.a . ubrr (USART baud Rate Register)
  UBRR0H = baudSetting >> 8; 
  UBRR0L = baudSetting;
  //set frameformat
  UCSR0C = SERIAL_8N1;
  //enable Rx, Tx
  UCSR0B = ((1 << RXEN0) | (1 << TXEN0));
}

void uart_transmit_char(unsigned char recieved_char){
  // wait for transmit buffer to be empty
  while(!(UCSR0A & (1 << UDRE0)));
  // load recieved_char into transmit register
  UDR0 = recieved_char;
}

char uart_recieve_char(void){
  //poll button while waiting for char
  while (!(UCSR0A & (1 << RXC0))){
    poll_button();
  }

  return UDR0;
}

void uart_recieve_str(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recieved_char;
  
  //read until newline or until buffer is full
  while (i < maxLength - 1){
    recieved_char = uart_recieve_char();
    if (recieved_char == '\n') {
      break;
    }
    buffer[i++] = recieved_char;
  }
  //null-terminate the string to know where string ends
  buffer[i] = '\0'; 
}

void uart_transmit_str(const char *str){
  while (*str) {
    uart_transmit_char(*str++);
  }
}

void uart_echo_char(){
  char recieved_char = uart_recieve_char();
  uart_transmit_char(recieved_char);
  uart_transmit_char('\n');
}

// void uart_echo_str(char *str){
//   uart_rec_str(str, sizeof(str));
//   uart_put_str(str);
//   uart_put_str("\n");
// }