#include <util/delay.h>
#include "button.h"
#include "bit_manipulation.h"
#include "led.h"

//checking input pin. 0 = button pressed
#define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0)
#define OUTPUT_CONFIG(byte, nbit) BIT_CLEAR(byte ,nbit)
#define PULL_UP_ACTIVATE(byte, nbit) BIT_SET(byte, nbit)

void BUTTON::button_initiate(void){
  OUTPUT_CONFIG(DDRx, nbit);
  PULL_UP_ACTIVATE(PORTx, nbit);
}

void BUTTON::poll_button(void){
  //lazy debounce
  _delay_ms(200); 
  if(BUTTON_PRESSED(PINx, nbit)){
    led.state = !led.state; 
  }
}