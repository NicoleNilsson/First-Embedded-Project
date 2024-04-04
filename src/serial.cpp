#include <avr/io.h>
#include "serial.h"

#define SERIAL_8N1 0x06

void Serial::uart_initiate(){
  uint16_t baud_rate = 9600;
  //calculate baud setting value
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

char Serial::uart_recieve_char(void){
  //waiting to recieve data
  // while (!HAS_CHAR);
  //return recieved char  
  return UDR0;
}

void Serial::uart_transmit_char(unsigned char recieved_char){
  //wait for data register to be empty
  while(!REGISTER_EMPTY);
  //load recieved_char into transmit register
  UDR0 = recieved_char;
}

void Serial::uart_recieve_str(char *buffer, uint8_t max_length){
  uint8_t i = 0;
  char recieved_char;
  
  //recieve data until newline or until buffer is full
  while (i < max_length - 1){
    if(HAS_RECIEVED_CHAR){
      recieved_char = uart_recieve_char();
      if (recieved_char == '\n') {
        break;
      }else{
        buffer[i++] = recieved_char;  
      }
    }
  }
  //null-terminate the string to know where it ends
  buffer[i] = '\0'; 
}

void Serial::uart_transmit_str(const char *str){
  while (*str) {
    uart_transmit_char(*str++);
  }
}

void Serial::uart_echo_char(){
  char recieved_char = uart_recieve_char();
  uart_transmit_char(recieved_char);
  uart_transmit_char('\n');
}