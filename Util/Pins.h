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

    // Set Type Methods

    static void setTypeByMask(uint8_t mask) {
        _SFR_IO8(ddr) = mask;
    }

    template<IOType type>
    static void setAllType() {
        if constexpr (type == IOType::Input) {
            setTypeByMask(0);
        } else {
            setTypeByMask(0xff);
        }
    }

    // Write Value Methods

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

    template<bool value>
    static void writePin(uint8_t i) {
        auto currentValue = readAll<PortType::Port>();

        if constexpr (value) {
            writeMask(static_cast<uint8_t>(currentValue | (1 << i)));
        } else {
            writeMask(static_cast<uint8_t>(currentValue & ~(1 << i)));
        }
    }

    static void writePin(uint8_t i, bool value) {
        if (value) {
            writePin<true>(i);
        } else {
            writePin<false>(i);
        }
    }

    // Read Value Methods

    template<PortType type>
    static uint8_t readAll() {
        constexpr auto address = type == PortType::Pin ? pin : port;

        return _SFR_IO8(address);
    }

    template<PortType type>
    static bool readPin(uint8_t i) {
        const auto value = readAll<type>();

        return static_cast<bool>((value & (1 << i)) >> i);
    }

    template<PortType type>
    static bool anyHigh() {
        auto value = readAll<type>();

        return value;
    }

    template<PortType type>
    static bool anyLow() {
        return invert(readAll<type>());
    }

private:
    static constexpr uint8_t pin = static_cast<uint8_t>(TPort);
    static constexpr uint8_t ddr = static_cast<const uint8_t>(static_cast<uint8_t>(TPort) + 1);
    static constexpr uint8_t port = static_cast<const uint8_t>(static_cast<uint8_t>(TPort) + 2);

    static uint8_t invert(uint8_t mask) {
        return static_cast<uint8_t>(mask ^ 0xff);
    }
};

#endif //AVR_LED_H
