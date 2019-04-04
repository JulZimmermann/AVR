//
// Created by konrad on 01.04.19.
//

#ifndef AVR_CLOCK_H
#define AVR_CLOCK_H

#include <stdint.h>
#include <stddef.h>

constexpr uint32_t T_CPU = 8000000;

template<typename T>
constexpr T calcComp(uint16_t prescaler, size_t millis) {
    return (T_CPU / (prescaler * (millis / 1000))) - 1;
}

#endif //AVR_CLOCK_H
