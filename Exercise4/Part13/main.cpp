
#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>
#include <avr/interrupt.h>

constexpr int ALL_HIGH = 0xFF;
constexpr int ALL_LOW = 0;

int blink();
void led(uint8_t count);

int main() {
    DDRD = ALL_LOW;
    DDRB = ALL_HIGH;
    DDRC = ALL_HIGH;

    PORTB = ALL_HIGH;
    PORTC = ALL_HIGH;

    TIMSK |= (1<<OCIE0);                    // Enable Timer 0 Overflow interrupt
    TCCR0 |= (1<<CS01)|(1<<CS00);//|(1<<CS02);           // Start timer0 with prescaler 1024

    OCR0 = 1;

    TCCR1B |= (1<<CS12)|(1<<CS10);
    OCR1A = uint16_t (F_CPU/1024) - 1;

    TIMSK |= (1<<OCIE1A);

    sei();                               // Set the I-bit in SREG

    for(;;);

    return 0;
}

ISR (TIMER0_COMP_vect) {
    PORTB = PORTB ^ ALL_HIGH;
}

ISR (TIMER1_COMPA_vect) {
    PORTC = PORTC ^ ALL_HIGH;
}