#include <avr/io.h>
#include "bit_manipulation.h"
#include "led.h"

#ifndef __BUTTON_H
#define __BUTTON_H

class BUTTON{
public:
    BUTTON(const uint8_t nbit, volatile uint8_t &DDRx, volatile uint8_t &PORTx, volatile uint8_t &PINx, LED &led)
            :nbit(nbit), DDRx(DDRx), PORTx(PORTx), PINx(PINx), led(led){
        button_initiate();
    }
    const uint8_t nbit;
    volatile uint8_t &DDRx;
    volatile uint8_t &PORTx;
    volatile uint8_t &PINx;
    LED &led;
    void pollButton(void);     

private:
    void button_initiate(void);
};


#endif