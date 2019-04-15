#include <stddef.h>

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t count = 0;

int main() {
    // Set LEDs as Output
    DDRC = 0xFF;

    // Disable all LEDs (LEDS are active low)
    PORTC = 0xFF;

    // Enable Timer 0 compare interrupt
    TIMSK |= (1<<OCIE1A);

    // Start timer0 with prescaler 1024
    TCCR1B |= (1<<WGM12)|(1<<CS12)|(1<<CS10);

    OCR1A = (uint16_t) ((F_CPU/1024) - 1) * 8;

    sei();

    while(true);
}

ISR (TIMER1_COMPA_vect) {
    ++count;
    PORTC = ~count;
}