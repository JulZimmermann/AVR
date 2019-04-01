//
// Created by Lars on 01.04.2019.
//

#ifndef AVR_SONG_H
#define AVR_SONG_H

#include "Note.h"

template <int size>
 class Song {
 public:
    void addNote(Note note, NoteLength length) {
        notes[currentSize] = note;
        noteLengths[currentSize] = length;

        ++currentSize;
    }

    int currentSize = 0;
    Note notes[size];
    NoteLength noteLengths[size];
};

#endif //AVR_SONG_H
