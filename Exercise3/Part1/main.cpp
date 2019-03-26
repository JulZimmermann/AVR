
#include <avr/io.h>

int led() {

}

int main() {
    while (1) {
        led();
        DDRD = 0;
        DDRB = 0xff;

        PORTB = 0;
        PIND = 0;
    }

    return 0;
}

