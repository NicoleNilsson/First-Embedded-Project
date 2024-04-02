#include <avr/io.h>
#include <stdio.h>
#include "led.h"
#include "bit_manipulation.h"
#include "serial.h"

#define LED_POWER_THRESHOLD 127
#define LED_POWER_MAX 255
#define LED_POWER_MIN 0

void led_initiate(void){
  //set pin on DDRB as 1 to configure pin as output
  BIT_SET(DDRB, LED_PIN); 
}

void led_serial_control(void){
  static uint16_t led_power = 0;
  static char str[32];

  uart_recieve_str(str, sizeof(str));
  uart_transmit_str(str);
  uart_transmit_str("\n");


  int8_t result = sscanf(str, "ledpower %d", &led_power);

  if(result == 1){
    if(led_power > LED_POWER_THRESHOLD && led_power <= LED_POWER_MAX){
      //switch led on
      BIT_SET(PORTB, LED_PIN);
    }else if(led_power <= LED_POWER_THRESHOLD && led_power >= LED_POWER_MIN){
      //switch led off
      BIT_CLEAR(PORTB, LED_PIN); 
    }else{
      uart_transmit_str("Invalid led power value\n");
    }
  }
}