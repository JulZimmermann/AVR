//
// Created by julian on 04.04.19.
//

#ifndef AVR_PLAYER_H
#define AVR_PLAYER_H

template<int size>
class Player {

public:
    static void playSong(const Song<size>& song) {
        TIMSK |= (1 << OCIE1A);
        TIMSK |= (1 << OCIE0);

        TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);       // Start timer1 with prescaler 1024 and compare match reset
        OCR1A = 10;

        TCCR0 |= (1 << CS02) | (1 << CS00);           // Start timer0 with prescaler 1024

        sei();

        while (true);
    }


private:
    static int count = 0;
    static Song<size> song;

    static void flashLed(Note note) {
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

    static void soundInterrupt() __asm__("__vector_10") __attribute__((__signal__, __used__, __externally_visible__)) {
        PORTB = PORTB ^ 0xFF;
        TCNT0 = 0;
    }

    static void playInterrupt() __asm__("__vector_7") __attribute__((__signal__, __used__, __externally_visible__)) {
        count %= enten.currentSize;

        if(pause) {
            TIMSK &= ~(1 << OCIE0);
            OCR1A = calcComp<uint16_t>(1024, 50);

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
        OCR1A = 3 * calcComp<uint16_t>(1024, static_cast<size_t>(enten.noteLengths[count]));

        ++count;
        pause = true;
    }

};


#endif //AVR_PLAYER_H
