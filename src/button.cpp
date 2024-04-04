#include <util/delay.h>
#include "button.h"
#include "bit_manipulation.h"
#include "led.h"

//checking input pin. 0 = button pressed
#define BUTTON_PRESSED(byte, nbit) (BIT_CHECK(byte, nbit) == 0)
//set bit as 0 to configure pin as input
#define INPUT_CONFIG(byte, nbit) BIT_CLEAR(byte ,nbit)
//set bit as 1 to activate pull-up resistor
#define PULLUP_ACTIVATE(byte, nbit) BIT_SET(byte, nbit)

void BUTTON::button_initiate(void){
  INPUT_CONFIG(DDRx, nbit);
  PULLUP_ACTIVATE(PORTx, nbit);
}

void BUTTON::pollButton(void){
  //lazy debounce
  _delay_ms(200); 
  if(BUTTON_PRESSED(PINx, nbit)){
    led.state = !led.state; 
  }
}