#include <Pins.h>
#include <avr/interrupt.h>

using Switches = Pins<Port::D>;
using Speaker = Pins<Port::B>;
using LEDs = Pins<Port::C>;

int main() {
    Switches::setAllInput();
    Speaker::setAllOutput();
    LEDs::setAllOutput();

    TCCR0 |= (1 << CS01) | (1 << CS00);           // Start timer0 with prescaler 1024

    sei();

    while (true) {

        LEDs::writeMask(Switches::readAll<PortType::Pin>());

        for (uint8_t i = 0; i < 8; ++i) {
            const bool pressed = !Switches::readPin<PortType::Pin>(i);
            if (pressed) {
                OCR0 = (uint8_t) (255 / 8 * (i + 1));
                TIMSK |= (1 << OCIE0);
            }
        }

        if (!Switches::anyLow<PortType::Pin>()) {
            TIMSK &= ~(1 << OCIE0);
        }
    }

}

ISR (TIMER0_COMP_vect) {
    PORTB = PORTB ^ 0xFF;
    TCNT0 = 0;
}