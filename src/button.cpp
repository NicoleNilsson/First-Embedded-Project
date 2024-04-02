#include <avr/io.h>
#include <util/delay.h>
// #include <stdio.h>
#include "button.h"
#include "bit_manipulation.h"
#include "led.h"

//checking input pin. 0 = button pressed
#define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0) 

void button_initiate(void){
  //set pin on DDRB as 0 to configure pin as input
  BIT_CLEAR(DDRB, BUTTON_PIN); 
  //set pin on PORTB as 1 to activate pull-up resistor
  BIT_SET(PORTB, BUTTON_PIN);
}

void poll_button(void){
  //lazy debounce
  _delay_ms(200);
  if(BUTTON_PRESSED(PINB, BUTTON_PIN)){ 
    //turn led on or off
    BIT_FLIP(PORTB, LED_PIN);
  }
}