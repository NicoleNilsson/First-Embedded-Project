#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

#define SERIAL_8N1 0x06

void Serial::initiateUART(){
  //calculate baud setting value
  uint16_t baudSetting = (F_CPU / 4 / baudRate - 1) / 2;
  //double speed mode
  UCSR0A = 1 << U2X0; 

  //store high byte of baud_setting
  UBRR0H = baudSetting >> 8; 
  //store low byte of baud_setting
  UBRR0L = baudSetting;

  //set frame format
  UCSR0C = SERIAL_8N1; //(1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0)

  //enable UART reciever and transmitter
  UCSR0B = ((1 << RXEN0) | (1 << TXEN0));
}

char Serial::recieveChar(void){
  //waiting to recieve data
  while(!HAS_RECIEVED_CHAR);
  //return recieved char 
  return UDR0;
}

void Serial::transmitChar(unsigned char recievedChar){
  //wait for data register to be empty
  while(!REGISTER_EMPTY);
  //load recievedChar into transmit register
  UDR0 = recievedChar;
}

void Serial::recieveString(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recievedChar;
  
  //recieve data until newline or until buffer is full
  while (i < maxLength - 1){
    recievedChar = recieveChar();
    if (recievedChar == '\n') {
      break;
    }else{
      buffer[i++] = recievedChar;  
    }
  }
  //null-terminate the string to know where it ends
  buffer[i] = '\0'; 
}

void Serial::transmitString(const char *str){
  while (*str) {
    transmitChar(*str++);
  }
}

void Serial::echoChar(){
  char recievedChar = recieveChar();
  transmitChar(recievedChar);
  transmitChar('\n');
}