#include <avr/io.h>

#ifndef __LED_H
#define __LED_H

const uint8_t LED_PIN = 0; //define led pin (will be used on port B, aka pin 8 on freenove)
const uint8_t BUTTON_PIN = 1; //define led pin (will be used on port B, aka 9 on freenove)

void led_init(void);

#endif