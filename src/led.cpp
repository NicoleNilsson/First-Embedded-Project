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

void LED::initiateLED(void){
  INPUT_CONFIG(DDRx, nbit); 
}

void LED::LEDSerialControl(Serial &serial){
  char str[16];

  serial.recieveString(str, sizeof(str));
  serial.transmitString(str);
  serial.transmitChar('\n');

  uint8_t result = sscanf(str, "ledpower %d", &LEDPower);

  if(result == 1){
    if(LEDPower > LED_POWER_THRESHOLD && LEDPower <= LED_POWER_MAX){
      state = true;
    }else if(LEDPower <= LED_POWER_THRESHOLD && LEDPower >= LED_POWER_MIN){
      state = false;
    }else{
      serial.transmitString("Invalid led power value\n");
    }
  }
}

void LED::toggleLED(void){
  if(state == true){
    LED_ON;
  }else if(state == false){
    LED_OFF;
  }
}