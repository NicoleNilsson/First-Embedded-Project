#include "serial.h"
#include "led.h"
#include "button.h"
#include <stdio.h>

int main(void){
  //setup
  Serial uart;
  LED redLED(0, DDRB, PORTB); //aka pin 8 on freenove
  BUTTON redButton(1, DDRB, PORTB, PINB, redLED); //aka pin 9 on freenove

  //main loop
  while(1){
    if(HAS_RECIEVED_CHAR){
    redLED.led_serial_control(uart);
    }else{
      redButton.poll_button();
    }

    redLED.toggle_led();
  }

  return 0;
}