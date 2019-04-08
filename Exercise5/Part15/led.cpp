#include <UART.h>
#include <Pins.h>

using LEDs = Pins<Port::C>;
using Buttons = Pins<Port::A>;

int main() {
    LEDs::setAllOutput();
    Buttons::setAllInput();

    // Disable leds. Default is on
    LEDs::writeAllHigh();

    UART uart(9600);

    while(true) {
        uint8_t ledMask = uart.readByte();
        LEDs::writeMask(ledMask);

        uint8_t buttonMask = Buttons::readAll<PortType::Pin>();
        uart.writeByte(buttonMask);
    }

}