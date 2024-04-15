#include <avr/io.h>

#ifndef __SERIAL_H
#define __SERIAL_H

#define HAS_RECIEVED_CHAR (UCSR0A & (1 << RXC0))
#define REGISTER_EMPTY (UCSR0A & (1 << UDRE0))

enum serialErrorCodes{
    SUCCESS,
    STRING_TOO_LONG
};

class Serial{
public:
    Serial(const uint16_t baudRate)
            :baudRate(baudRate){
        initiateUART();
    }

    void transmitChar(unsigned char data);
    char recieveChar(void);
    void transmitString(const char *str);
    uint8_t recieveString(char *buffer, uint8_t maxLength);
    void echoChar();
    void transmitInteger(const uint16_t& value);

private:
    const uint16_t baudRate;
    void initiateUART();
};

#endif