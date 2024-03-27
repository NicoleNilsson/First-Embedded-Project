#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BIT_SET(byte, nbit) ((byte) |= (1 << (nbit))) //set bit on byte as 1
#define BIT_CLEAR(byte ,nbit) ((byte) &= ~(1 << (nbit))) //set bit on byte as 0
#define BIT_CHECK(byte, nbit) ((byte) & (1 << (nbit))) //check if bit on byte is 1
#define BIT_FLIP(byte, nbit) ((byte) ^= (1 << (nbit))) //flip all bits (so all 1 set as 0, all 0 set as 1)

#define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0) //checking input pin. 0 = button pressed

#define SERIAL_8N1 0x06

const uint8_t LED_PIN = 0; //define led pin (will be used on port B, aka pin 8 on freenove)
const uint8_t BUTTON_PIN = 1; //define led pin (will be used on port B, aka 9 on freenove)

void uart_transmit_char (unsigned char data){
  // wait for transmit buffer to be empty
  while(!(UCSR0A & (1 << UDRE0)));
  // load data into transmit register
  UDR0 = data;
}

char uart_get_char (void){
  // wait for data
  while (!(UCSR0A & (1 << RXC0)));
  // return data
  return UDR0;
}

void uart_transmit_string(const char *str) {
  //transmit all characters in string
  while (*str) {
    uart_transmit_char(*str++);
  }
}

void uart_receive_string(char *buffer, uint8_t max_length) {
  uint8_t i = 0;
  char received_char;
  
  // read until newline or until buffer is full
  while (i < max_length - 1) {
    received_char = uart_get_char();
    if (received_char == '\n') {
      break;
    }
    buffer[i++] = received_char;
  }
  buffer[i] = '\0'; // null-terminate the string to know where string ends
}

int main(void){
  //setup
  BIT_CLEAR(DDRB, BUTTON_PIN); //set pin on DDRB as 0 to configure pin as input
  BIT_SET(PORTB, BUTTON_PIN); //set pin on PORTB as 1 to activate pull-up resistor
  BIT_SET(DDRB, LED_PIN); //set pin on DDRB as 1 to configure pin as output

  //baud=9600, frameformat=8N1
  uint16_t baud = 9600;
  uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
  UCSR0A = 1 << U2X0; //double speed mode
  // assign the baud_setting , a.k.a . ubrr (USART Baud Rate Register)
  UBRR0H = baud_setting >> 8; 
  UBRR0L = baud_setting;
  //set frameformat
  UCSR0C = SERIAL_8N1;
  //enable Rx, Tx
  UCSR0B = ((1 << RXEN0) | (1 << TXEN0));

  char received_string[50]; //what size to use here? maybe implement safety somehow

  //main loop
  while(1){
    _delay_ms(100);
    if(BUTTON_PRESSED(PINB, BUTTON_PIN)){ 
      // LED_ON = !LED_ON;
      // if(LED_ON == true){
      //   BIT_SET(PORTB, LED_PIN); //set pin 0 on port B as 1 and turn led on
      // }else if(LED_ON == false){
      //   BIT_CLEAR(PORTB, LED_PIN); //clear pin 0 on port B and turn led off
      // }
      BIT_FLIP(PORTB, LED_PIN);
    }

    uart_receive_string(received_string, sizeof(received_string)); //makes button stop working
    uart_transmit_string(received_string);
    uart_transmit_string("\n"); // Add newline for readability
  }

  return 0;
}