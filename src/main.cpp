#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BIT_SET(byte, nbit) ((byte) |= (1<<(nbit)))
#define BIT_CLEAR(byte ,nbit) ((byte) &= ~(1<<(nbit)))

const uint8_t LED_PIN = 0; //define led pin

int main(void){
  //setup
  BIT_SET(DDRB, LED_PIN);
  //main loop
  while(1){
    _delay_ms(1000); //wait 500ms
    BIT_SET(PORTB, LED_PIN); //set pin 0 on port B (aka freenove pin 8) as output and turn led on
    _delay_ms(1000); //wait 500ms
    BIT_CLEAR(PORTB, LED_PIN); //clear pin 0 on port B and turn led off
  }

  return 0;
}