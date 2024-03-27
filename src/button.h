#include "bit_manipulation.h"

#ifndef __BUTTON_H
#define __BUTTON_H

const uint8_t BUTTON_PIN = 1; //define led pin (will be used on port B, aka 9 on freenove)

void button_init(void);
void poll_button(void);

#endif