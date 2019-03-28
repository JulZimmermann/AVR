#include <stddef.h>

#include <avr/io.h>
#include <util/delay.h>

#include <Pins.h>
#include <Port.h>

using Switches = Pins<Port::D>;
using Leds = Pins<Port::B>;

int main() {
    Switches::setAllType<IOType::Input>();
    Leds::setAllType<IOType::Output>();

    // Disable all LEDs. LEDs are active low
    Leds::writeAllHigh();

    uint8_t count = 0;
    bool werePressedBefore = false;

    while (true) {
        const bool isPressedNow = Switches::anyLow<PortType::Pin>();

        if (!werePressedBefore && isPressedNow) {
            werePressedBefore = true;
            Leds::writeMaskInverted(++count);
        }

        if (!isPressedNow) {
            werePressedBefore = false;
            _delay_ms(100);
        }
    }
}
