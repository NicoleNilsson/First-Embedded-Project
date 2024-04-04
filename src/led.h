#include <avr/io.h>
#include "serial.h"

#ifndef __LED_H
#define __LED_H

class LED{
public:
    LED(const uint8_t nbit, volatile uint8_t &DDRx, volatile uint8_t &PORTx)
        : nbit(nbit), DDRx(DDRx), PORTx(PORTx) {
            led_initiate();
        }

    const uint8_t nbit;
    volatile uint8_t &DDRx;
    volatile uint8_t &PORTx;
    bool state = false;
    void led_serial_control(Serial &serial);
    void toggle_led(void);

private:
void led_initiate(void);
};

#endif