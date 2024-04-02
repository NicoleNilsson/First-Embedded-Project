#include <avr/io.h>
#include "button.h"

#define SERIAL_8N1 0x06
#define task poll_button()

void uart_initiate(){
  uint16_t baud_rate = 9600;
  //calculate baud rade setting value
  uint16_t baud_setting = (F_CPU / 4 / baud_rate - 1) / 2;
  //double speed mode
  UCSR0A = 1 << U2X0; 

  //store high byte of baud_setting
  UBRR0H = baud_setting >> 8; 
  //store low byte of baud_setting
  UBRR0L = baud_setting;

  //set frame format
  UCSR0C = SERIAL_8N1; //(1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0)

  //enable UART reciever and transmitter
  UCSR0B = ((1 << RXEN0) | (1 << TXEN0));
}

void uart_transmit_char(unsigned char recieved_char){
  //wait for data register to be empty
  while((UCSR0A & (1 << UDRE0)) == 0);
  //load recieved_char into transmit register
  UDR0 = recieved_char;
}

char uart_recieve_char(void){
  //perform task while waiting to recieve data
  while ((UCSR0A & (1 << RXC0)) == 0){
    task;
  }
  //return recieved char  
  return UDR0;
}

void uart_recieve_str(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recieved_char;
  
  //recieve data until newline or until buffer is full
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