#include <avr/io.h>

#ifndef __LED_H
#define __LED_H

//define led pin (will be used on port B, aka pin 8 on freenove)
const uint8_t LED_PIN = 0; 

void led_initiate(void);
void led_serial_control(void);

#endif