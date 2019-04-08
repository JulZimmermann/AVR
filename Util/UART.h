//
// Created by julian on 08.04.19.
//

#ifndef AVR_UART_H
#define AVR_UART_H

#include <stdint.h>
#include <stddef.h>

class UART {

public:
    static void enableSync();
    static void enableAsync();

    static void setBaud(uint16_t baud);

    static void writeByte(uint8_t byte);
    static void writeString(const char* str);

    static uint8_t readByte();
    static void readNBytes(size_t size, uint8_t *buffer);
    static void readString(char* string, size_t stringSize);

private:
    static constexpr uint32_t SYSTEM_CLOCK = 8000000;

    static constexpr uint16_t calcUbrr(uint16_t baud);

};


#endif //AVR_UART_H
