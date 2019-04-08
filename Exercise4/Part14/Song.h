//
// Created by Lars on 01.04.2019.
//

#ifndef AVR_SONG_H
#define AVR_SONG_H

#include "Note.h"

template <int maxSize>
 class Song {
 public:
    void addNote(Note note, NoteLength length) {
        notes[size] = note;
        noteLengths[size] = length;

        ++size;
    }

    int size = 0;
    Note notes[maxSize];
    NoteLength noteLengths[maxSize];

    template <int songSize, Port SpeakerPort, Port LEDsPort>
    friend class Player;
};

#endif //AVR_SONG_H
