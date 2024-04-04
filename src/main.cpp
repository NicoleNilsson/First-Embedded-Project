#include "serial.h"
#include "led.h"
#include "button.h"
#include <stdio.h>

int main(void){
  //setup
  Serial uart(9600);
  LED redLED(0, DDRB, PORTB); //aka pin 8 on freenove
  BUTTON redButton(1, DDRB, PORTB, PINB, redLED); //aka pin 9 on freenove

  //main loop
  while(1){
    if(HAS_RECIEVED_CHAR){
      redLED.LEDSerialControl(uart);
    }else{
      redButton.pollButton();
    }
    redLED.toggleLED();
  }

  return 0;
}