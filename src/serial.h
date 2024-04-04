#include <avr/io.h>

#ifndef __SERIAL_H
#define __SERIAL_H

#define HAS_RECIEVED_CHAR (UCSR0A & (1 << RXC0))
#define REGISTER_EMPTY (UCSR0A & (1 << UDRE0))

class Serial{
public:
    Serial(const uint16_t baudRate)
            :baudRate(baudRate){
        initiateUART();
    }

    void transmitChar(unsigned char data);
    char recieveChar(void);
    void transmitString(const char *str);
    void recieveString(char* buffer, uint8_t maxLength);
    void echoChar();

private:
    const uint16_t baudRate;
    void initiateUART();
};

#endif