#include "serial.h"
#include "button.h"
#include "led.h"
#include <stdio.h>

int main(void){
  //setup
  uart_initiate();
  led_initiate();
  button_initiate();

  //main loop
  while(1){
    led_serial_control();
  }

  return 0;
}