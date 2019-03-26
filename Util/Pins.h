//
// Created by julian on 26.03.19.
//

#ifndef AVR_LED_H
#define AVR_LED_H

#include <avr/io.h>

#include "Port.h"

template <Port TPort>
class Pins {
public:

    template <IOType type>
    void setType() {
        if constexpr (type == IOType::Input) {
            doSetMask<PortType::Ddr>(0);
        } else {
            doSetMask<PortType::Ddr>(0xff);
        }
    }

    void writeMask(uint8_t i) {
        doSetMask<PortType::Port>(i);
    }

    void writeMaskInverted(uint8_t i) {
        doSetMask<PortType::Port>(static_cast<uint8_t>(i ^ 0xff));
    }

    void writeAllHigh() {
        doSetMask<PortType::Port>(0xff);
    }

    void writeAllLow() {
        doSetMask<PortType::Port>(0);
    }

    void writePin(uint8_t i, bool value) {
        if(value) {
            writePinTrue(i);
        } else {
            writePinFalse(i);
        }
    }

    void writePinTrue(uint8_t i) {
        auto currentValue = readAll<PortType::Port>();
        writeMask(static_cast<uint8_t>(currentValue | (1 << i)));
    }

    void writePinFalse(uint8_t i) {
        auto currentValue = readAll<PortType::Port>();
        writeMask(static_cast<uint8_t>(currentValue & ~(1 << i)));
    }

    template <PortType type>
    uint8_t readAll() {
        constexpr auto adress = getAdress<type>();

        return _SFR_IO8(adress);
    }

    template <PortType type>
    bool readPin(uint8_t i) {
        uint8_t value = readAll<type>();

        return static_cast<bool>((value & ( 1 << i )) >> i);
    }

    template <PortType type>
    bool anyHigh() {
        auto value = readAll<type>();

        return value;
    }

    template <PortType type>
    bool anyLow() {
        return static_cast<bool>(readAll<type>() ^ 0xff);
    }

private:
    static constexpr uint8_t pin = static_cast<uint8_t>(TPort);
    static constexpr uint8_t ddr = static_cast<const uint8_t>(static_cast<uint8_t>(TPort) + 1);
    static constexpr uint8_t port = static_cast<const uint8_t>(static_cast<uint8_t>(TPort) + 2);

    template <PortType type>
    static constexpr uint8_t getAdress() {
        if constexpr(type == PortType::Ddr) {
            return ddr;
        }

        if constexpr(type == PortType::Pin) {
            return pin;
        }

        if constexpr(type == PortType::Port) {
            return port;
        }

        return 0;
    }

    template <PortType type>
    void doSetMask(uint8_t i) {
        constexpr auto adress = getAdress<type>();
        _SFR_IO8(adress) = i;
    }

};


#endif //AVR_LED_H
