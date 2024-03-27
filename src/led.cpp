#include <avr/io.h>
#include "led.h"
#include "bit_manipulation.h"

void led_init(void){
    BIT_SET(DDRB, LED_PIN); //set pin on DDRB as 1 to configure pin as output
}