
#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>

constexpr int ALL_HIGH = 0xFF;
constexpr int ALL_LOW = 0;

int blink();
void led(uint8_t count);

int main() {
    DDRD = ALL_LOW;
    DDRB = ALL_HIGH;

    PORTB = ALL_HIGH;

    blink();

    return 0;
}

int blink() {
    uint8_t count = 0;
    bool isPressed = false;
    uint8_t flip = 0;

    while (true) {
        flip  = PIND ^ ALL_HIGH;

        if (!isPressed && flip) {
            isPressed = true;
            led(++count);
        }

        if (!flip) {
            isPressed = false;
            _delay_ms(100);
        }

    }
}

void led(uint8_t count) {
    PORTB = static_cast<uint8_t>(count ^ ALL_HIGH);
}