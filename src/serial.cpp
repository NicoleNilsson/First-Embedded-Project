#include <avr/io.h>
#include "button.h"

#define SERIAL_8N1 0x06

void uart_init(){
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

void uart_put_char(unsigned char data){
  // wait for transmit buffer to be empty
  while(!(UCSR0A & (1 << UDRE0)));
  // load data into transmit register
  UDR0 = data;
}

char uart_get_char(void){
  //poll button while waiting for data
  while (!(UCSR0A & (1 << RXC0))){
    poll_button();
  }
  // return data
  return UDR0;
}

void uart_put_str(const char *str){
  //transmit all characters in string
  while (*str) {
    uart_put_char(*str++);
  }
}

void uart_rec_str(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char inputChar;
  
  // read until newline or until buffer is full
  while (i < maxLength - 1) {
    inputChar = uart_get_char();
    if (inputChar == '\n') {
      break;
    }
    buffer[i++] = inputChar;
  }
  buffer[i] = '\0'; // null-terminate the string to know where string ends
}

void uart_echo_char(){
  char inputChar = uart_get_char();
  uart_put_char(inputChar);
  uart_put_char('\n');
}

void uart_echo_str(){
  char inputString[50];
  uart_rec_str(inputString, sizeof(inputString)); //recieve input to arduino
  uart_put_str(inputString); //return input from arduino
  uart_put_str("\n");
}