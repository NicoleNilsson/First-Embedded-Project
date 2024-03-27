#include <avr/io.h>
#include <stdio.h>
#include "led.h"
#include "bit_manipulation.h"
#include "serial.h"

void led_init(void){
  BIT_SET(DDRB, LED_PIN); //set pin on DDRB as 1 to configure pin as output
}

void led_serial_control(void){
  static uint8_t led_power = 0; //lampan kommer släckas om man skriver >255 pga uint8, gör det nåt?
  static char str[20];

  uart_echo_str(str); //recieve input string and echo back

  int8_t result = sscanf(str, "ledpower %hhu", &led_power);

  if(result == 1){
    if(led_power > 127 && led_power <= 255){
      BIT_SET(PORTB, LED_PIN); //set pin 0 on port B as 1 and turn led on
    }else if(led_power <= 127 && led_power >= 0){
      BIT_CLEAR(PORTB, LED_PIN); //clear pin 0 on port B and turn led off
    }
  }
}