#include "serial.h"
#include "button.h"
#include "led.h"
#include <stdio.h>

int main(void){
  //setup
  uart_init();
  led_init();
  button_init();

  uint8_t led_power = 0; //lampan kommer släckas om man skriver >255 pga uint8, gör det nåt?
  char recieved_string[20];

  //main loop
  while(1){
    //poll_button();
    //uart_echo_char();
    //uart_echo_str();

    uart_rec_str(recieved_string, sizeof(recieved_string));
    uart_put_str(recieved_string);
    uart_put_str("\n");

    int8_t result = sscanf(recieved_string, "ledpower %hhu", &led_power);

    if(result == 1){
      if(led_power > 127 && led_power <= 255){
        BIT_SET(PORTB, LED_PIN); //set pin 0 on port B as 1 and turn led on
      }else if(led_power <= 127 && led_power >= 0){
        BIT_CLEAR(PORTB, LED_PIN); //clear pin 0 on port B and turn led off
      }
    }
    
  }

  return 0;
}