#include <avr/io.h>

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
    void led_serial_control(void);

private:
void led_initiate(void);
};

#endif