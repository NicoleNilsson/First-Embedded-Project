#include <avr/io.h>
#include "button.h"

#define SERIAL_8N1 0x06

//initiate uart
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

//transmit char
void uart_put_char(unsigned char recieved_char){
  // wait for transmit buffer to be empty
  while(!(UCSR0A & (1 << UDRE0)));
  // load recieved_char into transmit register
  UDR0 = recieved_char;
}

//recieve char
char uart_get_char(void){
  //poll button while waiting for recieved_char
  while (!(UCSR0A & (1 << RXC0))){
    poll_button();
  }
  // return recieved_char
  return UDR0;
}

//recieve string
void uart_rec_str(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recieved_char;
  
  // read until newline or until buffer is full
  while (i < maxLength - 1) {
    recieved_char = uart_get_char();
    if (recieved_char == '\n') {
      break;
    }
    buffer[i++] = recieved_char;
  }
  buffer[i] = '\0'; // null-terminate the string to know where string ends
}

//transmit string
void uart_put_str(const char *str){
  while (*str) {
    uart_put_char(*str++);
  }
}

//echo recieved char
void uart_echo_char(){
  char recieved_char = uart_get_char();
  uart_put_char(recieved_char);
  uart_put_char('\n');
}

//echo recieved string
void uart_echo_str(char *str){
  uart_rec_str(str, sizeof(str)); //recieve input to arduino
  uart_put_str(str); //return input from arduino
  uart_put_str("\n");
}