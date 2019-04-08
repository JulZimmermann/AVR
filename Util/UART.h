//
// Created by julian on 08.04.19.
//

#ifndef AVR_UART_H
#define AVR_UART_H

#include <stdint.h>
#include <stddef.h>

class UART {

public:
    UART(uint16_t baud);

    void writeByte(uint8_t byte);
    void writeString(const char* str);

    uint8_t readByte();
    void readNByte(size_t size, uint8_t* buffer);
    void readString(char* string, size_t stringSize);

private:
    static constexpr uint32_t SYSTEM_CLOCK = 8000000;

    void setBaud(uint16_t baud);
    constexpr uint16_t calcUbrr(uint16_t baud);

};


#endif //AVR_UART_H
