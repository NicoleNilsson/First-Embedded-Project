#include <avr/io.h>
#include <util/delay.h>
// #include <stdio.h>
#include "button.h"
#include "bit_manipulation.h"
#include "led.h"

#define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0) //checking input pin. 0 = button pressed

void button_init(void){
    BIT_CLEAR(DDRB, BUTTON_PIN); //set pin on DDRB as 0 to configure pin as input
    BIT_SET(PORTB, BUTTON_PIN); //set pin on PORTB as 1 to activate pull-up resistor
}

void poll_button(void){
  _delay_ms(200); //lazy debounce
  if(BUTTON_PRESSED(PINB, BUTTON_PIN)){ 
    // LED_ON = !LED_ON;
    // if(LED_ON == true){
    //   BIT_SET(PORTB, LED_PIN); //set pin 0 on port B as 1 and turn led on
    // }else if(LED_ON == false){
    //   BIT_CLEAR(PORTB, LED_PIN); //clear pin 0 on port B and turn led off
    // }
    BIT_FLIP(PORTB, LED_PIN); //turn led on or off
  }
}