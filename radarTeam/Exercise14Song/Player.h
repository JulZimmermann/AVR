#ifndef AVR_PLAYER_H
#define AVR_PLAYER_H

#include <avr/interrupt.h>

#include <InterruptHandler.h>
#include <Pins.h>
#include <Clock.h>

#include "Song.h"

template <int songSize, Port SpeakerPort, Port LEDsPort>
class Player {

public:
    static void playSong(Song<songSize>& song) {
        Player::song = &song;

        TIMSK = (1 << OCIE1A) | (1 << OCIE0);
        TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
        TCCR0 |= (1 << CS02) | (1 << CS00);

        OCR1A = 10;

        sei();

        while (true);
    }


private:
    using Speaker = Pins<SpeakerPort>;
    using LEDs = Pins<LEDsPort>;

    static constexpr uint16_t prescalerFactor = 1024;
    static constexpr uint16_t noteSpeedFactor = 3;

    static int currentNoteIdx;
    static bool pause;
    static Song<songSize>* song;

    // Interrupt for TIMER_1. Creating the oscillation of the speaker
    CPP_ISR(TIMER0_COMP_vect) {
        const auto mask = Speaker::readAllPins();

        Speaker::writeMaskInverted(mask);

        TCNT0 = 0;
    }

    // Interrupt for TIMER_1. Creating the frequency and the length of a note
    CPP_ISR(TIMER1_COMPA_vect) {
        // Handle pause between notes
        if(pause) {
            TIMSK &= ~(1 << OCIE0);
            OCR1A = calcCompTime<uint16_t>(1024, 50);

            pause = false;

            return;
        }

        // Handle the note "pause"
        if(song->notes[currentNoteIdx] == Note::pause) {
            TIMSK &= ~(1 << OCIE0);
        } else {
            TIMSK |= (1 << OCIE0);
        }

        flashLEDs(song->notes[currentNoteIdx]);

        // Set frequency and length of current note
        OCR0 =  calcCompFreq<uint8_t>(prescalerFactor, currentNoteFreq());
        OCR1A = noteSpeedFactor * calcCompTime<uint16_t>(prescalerFactor, currentNoteLength());

        // Increase currentNoteIdx and set next call to pause
        currentNoteIdx = (currentNoteIdx + 1) % song->size;
        pause = true;
    }

    static size_t currentNoteFreq() {
        return static_cast<size_t>(song->notes[currentNoteIdx]);
    }

    static size_t currentNoteLength() {
        return static_cast<size_t>(song->noteLengths[currentNoteIdx]);
    }

    static void flashLEDs(Note note) {
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
            case Note::pause:break;
        }

        LEDs::writeMaskInverted(mask);
    }

};

template <int songSize, Port SpeakerPort, Port LEDsPort>
int Player<songSize, SpeakerPort, LEDsPort>::currentNoteIdx = 0;

template <int songSize, Port SpeakerPort, Port LEDsPort>
bool Player<songSize, SpeakerPort, LEDsPort>::pause = false;

template <int songSize, Port SpeakerPort, Port LEDsPort>
Song<songSize>* Player<songSize, SpeakerPort, LEDsPort>::song = nullptr;

#endif //AVR_PLAYER_H
