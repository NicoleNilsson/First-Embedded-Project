#include <stdio.h>
#include "led.h"
#include "bit_manipulation.h"
#include "serial.h"

#define LED_POWER_THRESHOLD 127
#define LED_POWER_MAX 255
#define LED_POWER_MIN 0

void LED::led_initiate(void){
  //set pin on DDRB as 1 to configure pin as output
  BIT_SET(DDRx, nbit); 
}

void LED::led_serial_control(void){
  static uint16_t led_power = 0;
  char str[16];

  uart_recieve_str(str, sizeof(str));
  uart_transmit_str(str);
  uart_transmit_str("\n");


  int8_t result = sscanf(str, "ledpower %d", &led_power);

  if(result == 1){
    if(led_power > LED_POWER_THRESHOLD && led_power <= LED_POWER_MAX){
      //switch led on
      BIT_SET(PORTx, nbit);
    }else if(led_power <= LED_POWER_THRESHOLD && led_power >= LED_POWER_MIN){
      //switch led off
      BIT_CLEAR(PORTx, nbit); 
    }else{
      uart_transmit_str("Invalid led power value\n");
    }
  }
}