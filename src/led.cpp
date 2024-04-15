#include <stdio.h>
#include "led.h"
#include "bit_manipulation.h"
#include "serial.h"

//set bit as 1 to configure pin as output
#define OUTPUT_CONFIG(byte, nbit) BIT_SET(byte, nbit)

#define LED_POWER_THRESHOLD 127
#define LED_POWER_MAX 255
#define LED_POWER_MIN 0

#define LED_ON BIT_SET(PORTx, nbit)
#define LED_OFF BIT_CLEAR(PORTx, nbit)

void LED::initiateLED(void){
  OUTPUT_CONFIG(DDRx, nbit); 
}

void LED::LEDSerialControl(Serial &serial){
  uint8_t strMaxLength = 16;
  char str[strMaxLength];

  uint8_t result1 = serial.recieveString(str, strMaxLength);
  if(result1 == STRING_TOO_LONG){
   serial.transmitString("Command can max be ");
   serial.transmitInteger(strMaxLength);
   serial.transmitString(" characters long");
   serial.transmitChar('\n');
    return;
  }
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
  }else{
    serial.transmitString("Unknown command");
    serial.transmitChar('\n');
  }
}

void LED::toggleLED(void){
  if(state == true){
    LED_ON;
  }else if(state == false){
    LED_OFF;
  }
}