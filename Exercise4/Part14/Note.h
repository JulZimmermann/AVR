//
// Created by Lars on 01.04.2019.
//

#ifndef AVR_NOTE_H
#define AVR_NOTE_H
enum class Note{
    c1 = 262,
    h = 247,
    a = 220,
    g = 196,
    f = 175,
    e = 165,
    d = 147,
    c = 131,
    pause = 0
};

enum class NoteLength{
    ganz = 1000,
    halb = 500,
    viertel = 250,
    achtel = 125,
    sechzentel = 63
};
#endif //AVR_NOTE_H
