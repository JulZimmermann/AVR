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
    return ((T_CPU / (double) prescaler) * (millis / 1000.0)) - 1;
}

template<typename T>
constexpr T calcCompFreq(uint16_t prescaler, size_t hz) {
    return ((T_CPU / (double) prescaler)  / (double) (hz * 2)) - 1;
}

#endif //AVR_CLOCK_H
