//
// Created by Lars on 01.04.2019.
//

#include "Song.h"
#include <Clock.h>
#include <avr/interrupt.h>

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

    while (true) {
//        for(size_t i = 0; i < enten.currentSize; ++i){
//
//        }
//        for (uint8_t i = 0; i < 8; ++i) {
//            const bool pressed = !Switches::readPin<PortType::Pin>(i);
//            if (pressed) {
//                OCR0 = (uint8_t) (255 / 8 * (i + 1));
//                TIMSK |= (1 << OCIE0);
//            }
//        }
//
//        if (!Switches::anyLow<PortType::Pin>()) {
//            TIMSK &= ~(1 << OCIE0);
//        }
    }

}

ISR (TIMER0_COMP_vect) {
    PORTB = PORTB ^ 0xFF;
    TCNT0 = 0;
}

ISR (TIMER1_COMPA_vect) {
    if (count < enten.currentSize) {
        OCR0 = calcComp<uint8_t>(1024, enten.notes[count]);
        OCR1A = calcComp<uint16_t>(1024, enten.noteLengths[count]);

        TIMSK |= (1 << OCIE0);
        ++count;
    } else {
        count = 0;
    }
}


