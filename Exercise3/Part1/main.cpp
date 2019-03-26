
#include <avr/io.h>
#include <stddef.h>

constexpr int ALL_OUTPUT = 0xff;
constexpr int ALL_INPUT = 0;

int blink();
void led(size_t count);

int main() {
    DDRD = ALL_INPUT;
    DDRB = ALL_OUTPUT;

    PORTB = 0;
    PIND = 0;

    blink();

    return 0;
}

int blink() {
    size_t count = 0;
    bool isPressed = false;

    while (true) {
        if (!isPressed && !PIND) {
            ++count;
            isPressed = true;

            led(count);
        }

        if (PIND) {
            isPressed = false;
        }
    }
}

void led(size_t count) {
    auto value = static_cast<uint8_t>(count % 8);

    value = ~value;

    PORTB = value;
}