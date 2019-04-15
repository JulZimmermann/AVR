//
// Created by julian on 26.03.19.
//

#ifndef AVR_LED_H
#define AVR_LED_H

#include <avr/io.h>

#include "Port.h"

template<Port TPort>
class Pins {
public:
    Pins() = delete;

    // Set Type Methods

    static void setTypeByMask(uint8_t mask) {
        _SFR_IO8(ddr) = mask;
    }

    static void setAllInput() {
        setTypeByMask(0);
    }

    static void setAllOutput() {
        setTypeByMask(0xff);
    }

    // Write Value Methods

    static void invertCurrentValue() {
        writeMaskInverted(readAllPins());
    }

    static void writeMask(uint8_t mask) {
        _SFR_IO8(port) = mask;
    }

    static void writeMaskInverted(uint8_t mask) {
        writeMask(invert(mask));
    }

    static void writeAllHigh() {
        writeMask(0xff);
    }

    static void writeAllLow() {
        writeMask(0);
    }

    static void writePin(uint8_t i, bool value) {
        const uint8_t currentValue = readAllPorts();

        if (value) {
            writeMask(static_cast<uint8_t>(currentValue | (1 << i)));
        } else {
            writeMask(static_cast<uint8_t>(currentValue & ~(1 << i)));
        }
    }

    // Read Value Methods

    static uint8_t readAllPins() {
        return _SFR_IO8(pin);
    }

    static uint8_t readAllPorts() {
        return _SFR_IO8(port);
    }

    static bool readSinglePin(uint8_t i) {
        const uint8_t value = readAllPins();

        return static_cast<bool>((value & (1 << i)) >> i);
    }

    static bool anyHigh() {
        return static_cast<bool>(readAllPins());
    }

    static bool anyLow() {
        return static_cast<bool>(invert(readAllPins()));
    }

private:
    static constexpr uint8_t pin = static_cast<uint8_t>(TPort);
    static constexpr uint8_t ddr = static_cast<const uint8_t>(static_cast<uint8_t>(TPort) + 1);
    static constexpr uint8_t port = static_cast<const uint8_t>(static_cast<uint8_t>(TPort) + 2);

    constexpr static uint8_t invert(uint8_t mask) {
        return static_cast<uint8_t>(mask ^ 0xff);
    }
};

#endif //AVR_LED_H
