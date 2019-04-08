#include <UART.h>
#include <Pins.h>

#include <avr/interrupt.h>

using LEDs = Pins<Port::C>;
using Buttons = Pins<Port::A>;

int main() {
    LEDs::setAllOutput();
    Buttons::setAllInput();

    // Disable leds. Default is on
    LEDs::writeAllHigh();

    UART::setBaud(9600);
    UART::enableAsync();

    sei();

    while(true) {
        uint8_t buttonMask = Buttons::readAll<PortType::Pin>();
        UART::writeByte(buttonMask);
    }

}

ISR(USART_RXC_vect) {
    uint8_t ledMask = UDR;
    LEDs::writeMask(ledMask);
}
