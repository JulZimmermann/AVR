
#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>

#include <Pins.h>
#include <Port.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
    Pins<Port::D> switches;
    switches.setType<IOType::Input>();

    Pins<Port::B> leds;
    leds.setType<IOType::Output>();

    // Disable all LEDs. LEDs are active low
    leds.writeAllHigh();

    uint8_t count = 0;
    bool isPressed = false;

    while (true) {
        const auto anyLow = switches.anyLow<PortType::Pin>();

        if (!isPressed && anyLow) {
            isPressed = true;
            leds.writeMaskInverted(++count);
        }

        if (!anyLow) {
            isPressed = false;
            _delay_ms(100);
        }
    }

}

#pragma clang diagnostic pop