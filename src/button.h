#include "bit_manipulation.h"

#ifndef __BUTTON_H
#define __BUTTON_H

//define button pin (will be used on port B, aka 9 on freenove)
const uint8_t BUTTON_PIN = 1; 

void button_initiate(void);
void poll_button(void);

#endif