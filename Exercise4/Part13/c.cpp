#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <Clock.h>

constexpr int ALL_HIGH = 0xFF;

uint8_t count = 0;

int main() {
    DDRC = ALL_HIGH;

    PORTC = ALL_HIGH;

    TIMSK |= (1<<OCIE1A);                    // Enable Timer 0 compare interrupt
    TCCR1B |= (1<<WGM12)|(1<<CS12)|(1<<CS10);           // Start timer0 with prescaler 1024

    OCR1A = calcComp<uint16_t>(1024, 1000);

    sei();                               // Set the I-bit in SREG

    while(true);
}

ISR (TIMER1_COMPA_vect) {
        ++count;

        uint8_t left = count / 10;
        uint8_t right = count % 10;

        uint8_t erg = left << 4 | right;

        PORTC = ~erg;
}

