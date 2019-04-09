#include <stddef.h>

#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRD = 0;
    DDRB = 0xff;

    // Disable all LEDs. LEDs are active low
    PORTB = 0xff;

    uint8_t count = 0;
    bool werePressedBefore = false;

    while (true) {
        const bool isPressedNow = static_cast<const bool>(PIND ^ 0xff);

        if (!werePressedBefore && isPressedNow) {
            werePressedBefore = true;
            PORTB = static_cast<uint8_t>(++count ^ 0xff);
        }

        if (!isPressedNow) {
            werePressedBefore = false;
            _delay_ms(100);
        }
    }
}
