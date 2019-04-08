//
// Created by julian on 08.04.19.
//

#include "UART.h"

#include <avr/io.h>

#include <stddef.h>

UART::UART(uint16_t baud) {
    setBaud(baud);

    //Enable UART
    UCSRB = (1 << RXEN) | (1 << TXEN);

    //Set Frame format: 8 bit data and 2 stop bits
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}

void UART::writeByte(uint8_t c) {
    // Wait for buffer to be empty
    while (!(UCSRA & (1 << UDRE)));

    UDR = c;
}

void UART::writeString(const char *str) {
    size_t i = 0;

    while(str[i] != '\0') {
        writeByte(str[i++]);
    }
}

void UART::setBaud(uint16_t baud) {
    uint16_t ubrr = calcUbrr(baud);

    UBRRH = static_cast<uint8_t >(ubrr >> 8);
    UBRRL = static_cast<uint8_t>(ubrr);
}

constexpr uint16_t UART::calcUbrr(uint16_t baud) {
    return SYSTEM_CLOCK / (static_cast<uint32_t >(16) * baud) - 1;
}
