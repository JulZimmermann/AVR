//
// Created by Lars on 01.04.2019.
//

#include <avr/interrupt.h>

#include <Clock.h>
#include <Pins.h>

#include "Song.h"

using Switches = Pins<Port::D>;
using Speaker = Pins<Port::B>;
using LEDs = Pins<Port::C>;

int count = 0;
Song<37> enten;

int main() {
    Switches::setAllInput();
    Speaker::setAllOutput();
    LEDs::setAllOutput();

    enten.addNote(Note::c, NoteLength::achtel);
    enten.addNote(Note::d, NoteLength::achtel);
    enten.addNote(Note::e, NoteLength::achtel);
    enten.addNote(Note::f, NoteLength::achtel);
    enten.addNote(Note::g, NoteLength::viertel);
    enten.addNote(Note::g, NoteLength::viertel);
    enten.addNote(Note::a, NoteLength::achtel);
    enten.addNote(Note::a, NoteLength::achtel);
    enten.addNote(Note::a, NoteLength::achtel);
    enten.addNote(Note::a, NoteLength::achtel);
    enten.addNote(Note::g, NoteLength::viertel);
    enten.addNote(Note::pause, NoteLength::viertel);
    enten.addNote(Note::f, NoteLength::achtel);
    enten.addNote(Note::f, NoteLength::achtel);
    enten.addNote(Note::f, NoteLength::achtel);
    enten.addNote(Note::f, NoteLength::achtel);
    enten.addNote(Note::e, NoteLength::viertel);
    enten.addNote(Note::e, NoteLength::viertel);
    enten.addNote(Note::g, NoteLength::achtel);
    enten.addNote(Note::g, NoteLength::achtel);
    enten.addNote(Note::g, NoteLength::achtel);
    enten.addNote(Note::g, NoteLength::achtel);
    enten.addNote(Note::c, NoteLength::viertel);

    TIMSK |= (1 << OCIE1A);                               // Enable Timer 1 compare interrupt
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);       // Start timer1 with prescaler 1024 and compare match reset
    OCR1A = 0;

    TCCR0 |= (1 << CS01) | (1 << CS00);           // Start timer0 with prescaler 1024

    sei();

    while (true);
}

ISR (TIMER0_COMP_vect) {
    PORTB = PORTB ^ 0xFF;
    TCNT0 = 0;
}

ISR (TIMER1_COMPA_vect) {
    if (count < enten.currentSize) {
        OCR0 = calcComp<uint8_t>(1024, static_cast<size_t>(enten.notes[count]));
        OCR1A = calcComp<uint16_t>(1024, static_cast<size_t>(enten.noteLengths[count]));

        TIMSK |= (1 << OCIE0);
        ++count;
    } else {
        count = 0;
    }
}


