#include "serial.h"
#include "button.h"
#include "led.h"

// #define BIT_SET(byte, nbit) ((byte) |= (1 << (nbit))) //set bit on byte as 1
// #define BIT_CLEAR(byte ,nbit) ((byte) &= ~(1 << (nbit))) //set bit on byte as 0
// #define BIT_CHECK(byte, nbit) ((byte) & (1 << (nbit))) //check if bit on byte is 1
// #define BIT_FLIP(byte, nbit) ((byte) ^= (1 << (nbit))) //flip all bits (so all 1 set as 0, all 0 set as 1)

// #define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0) //checking input pin. 0 = button pressed

// const uint8_t LED_PIN = 0; //define led pin (will be used on port B, aka pin 8 on freenove)
// const uint8_t BUTTON_PIN = 1; //define led pin (will be used on port B, aka 9 on freenove)


int main(void){
  //setup
  uart_init();
  led_init();
  button_init();
  // BIT_CLEAR(DDRB, BUTTON_PIN); //set pin on DDRB as 0 to configure pin as input
  // BIT_SET(PORTB, BUTTON_PIN); //set pin on PORTB as 1 to activate pull-up resistor
  // BIT_SET(DDRB, LED_PIN); //set pin on DDRB as 1 to configure pin as output

  //main loop
  while(1){
    uart_echo_str();
  }

  return 0;
}