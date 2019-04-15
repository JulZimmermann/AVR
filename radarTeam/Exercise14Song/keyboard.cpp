#include <avr/interrupt.h>

#include <Pins.h>

using Switches = Pins<Port::D>;
using Speaker = Pins<Port::B>;
using LEDs = Pins<Port::C>;

void playSound();

int main() {
    Switches::setAllInput();
    Speaker::setAllOutput();
    LEDs::setAllOutput();

    // Start timer0 with prescaler 1024
    TCCR0 |= (1 << CS01) | (1 << CS00);

    sei();

    while (true) {
        LEDs::writeMask(Switches::readAllPins());
        playSound();
    }

}

void playSound() {
    for (uint8_t i = 0; i < 8; ++i) {
        const bool pressed = !Switches::readSinglePin(i);
        if (pressed) {
            //Set timer compare register to manipulate the frequency of the speaker output
            OCR0 = (uint8_t) (255 / 8 * (i + 1));

            TIMSK |= (1 << OCIE0);
        }
    }

    if (!Switches::anyLow()) {
        TIMSK &= ~(1 << OCIE0);
    }
}

ISR (TIMER0_COMP_vect) {
    //Invert current value of the speaker to creating the oscillation
    Speaker::invertCurrentValue();

    // Reset overflow counter
    TCNT0 = 0;
}