#include "serial.h"
#include "led.h"
#include "button.h"
#include <stdio.h>

int main(void){
  //setup
  uart_initiate();
  LED redLED(0, DDRB, PORTB); //aka pin 8 on freenove
  BUTTON redButton(1, DDRB, PORTB, PINB, redLED); //aka pin 9 on freenove

  //main loop
  while(1){
    if(HAS_RECIEVED_CHAR){
    redLED.led_serial_control();
    }else{
      redButton.poll_button();
    }
  }

  return 0;
}