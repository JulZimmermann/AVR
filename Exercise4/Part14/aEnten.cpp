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

bool pause = false;
int count = 0;
Song<29> enten;

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

    enten.addNote(Note::pause, NoteLength::ganz);

    TIMSK |= (1 << OCIE1A);
    TIMSK |= (1 << OCIE0);

    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A = 10;

    TCCR0 |= (1 << CS02) | (1 << CS00);

    sei();

    while (true);
}

void flashLed(Note note) {
    uint8_t mask = 0;

    switch(note) {
        case Note::c:
            mask |= 1 << 7;
            break;
        case Note::d:
            mask |= 1 << 6;
            break;
        case Note::e:
            mask |= 1 << 5;
            break;
        case Note::f:
            mask |= 1 << 4;
            break;
        case Note::g:
            mask |= 1 << 3;
            break;
        case Note::a:
            mask |= 1 << 2;
            break;
        case Note::h:
            mask |= 1 << 1;
            break;
        case Note::c1:
            mask |= 1 << 0;
            break;
    }

    LEDs::writeMaskInverted(mask);
}

ISR (TIMER0_COMP_vect) {
    PORTB = PORTB ^ 0xFF;
    TCNT0 = 0;
}

ISR (TIMER1_COMPA_vect) {
    count %= enten.size;

    if(pause) {
        TIMSK &= ~(1 << OCIE0);
        OCR1A = calcCompTime<uint16_t>(1024, 50);

        pause = false;

        return;
    }

    flashLed(enten.notes[count]);

    if(enten.notes[count] == Note::pause) {
        TIMSK &= ~(1 << OCIE0);
    } else {
        TIMSK |= (1 << OCIE0);
    }

    OCR0 =  calcCompFreq<uint8_t>(1024, static_cast<size_t>(enten.notes[count]));
    OCR1A = 3 * calcCompTime<uint16_t>(1024, static_cast<size_t>(enten.noteLengths[count]));

    ++count;
    pause = true;
}

