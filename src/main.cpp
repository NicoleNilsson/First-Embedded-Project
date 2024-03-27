#include "serial.h"
#include "button.h"
#include "led.h"
#include <stdio.h>

int main(void){
  //setup
  uart_init();
  led_init();
  button_init();

  //main loop
  while(1){
    led_serial_control();
  }

  return 0;
}