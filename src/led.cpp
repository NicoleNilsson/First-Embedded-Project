#include <stdio.h>
#include "led.h"
#include "bit_manipulation.h"
#include "serial.h"

#define INPUT_CONFIG(byte, nbit) BIT_SET(byte, nbit)

#define LED_POWER_THRESHOLD 127
#define LED_POWER_MAX 255
#define LED_POWER_MIN 0

#define LED_ON BIT_SET(PORTx, nbit)
#define LED_OFF BIT_CLEAR(PORTx, nbit)

void LED::led_initiate(void){
  INPUT_CONFIG(DDRx, nbit); 
}

void LED::led_serial_control(Serial &serial){
  static uint16_t led_power = 0;
  char str[16];

  serial.uart_recieve_str(str, sizeof(str));
  serial.uart_transmit_str(str);
  serial.uart_transmit_str("\n");


  int8_t result = sscanf(str, "ledpower %d", &led_power);

  if(result == 1){
    if(led_power > LED_POWER_THRESHOLD && led_power <= LED_POWER_MAX){
      state = true;
    }else if(led_power <= LED_POWER_THRESHOLD && led_power >= LED_POWER_MIN){
      state = false;
    }else{
      serial.uart_transmit_str("Invalid led power value\n");
    }
  }
}

void LED::toggle_led(void){
  if(state == true){
    LED_ON;
  }else if(state == false){
    LED_OFF;
  }
}