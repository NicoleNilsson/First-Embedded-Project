#include <util/delay.h>
#include "button.h"
#include "bit_manipulation.h"
#include "led.h"

//checking input pin. 0 = button pressed
#define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0)

void BUTTON::button_initiate(void){
  //set pin on DDRB as 0 to configure pin as input
  BIT_CLEAR(DDRx, nbit);
  //set pin on PORTB as 1 to activate pull-up resistor
  BIT_SET(PORTx, nbit);
}

void BUTTON::poll_button(void){
  //lazy debounce
  _delay_ms(200); 
  if(BUTTON_PRESSED(PINx, nbit)){
    //turn led on or off
    BIT_FLIP(led.PORTx, led.nbit); 
  }
}