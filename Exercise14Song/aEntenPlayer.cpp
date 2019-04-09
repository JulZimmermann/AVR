#include "Player.h"

constexpr int songSize = 29;

constexpr auto SpeakerPort = Port::B;
constexpr auto LEDsPort = Port::C;

using Speaker = Pins<SpeakerPort>;
using LEDs = Pins<LEDsPort>;

using EntenPlayer = Player<songSize, SpeakerPort, LEDsPort>;

void fillSong(Song<songSize> &song);

int main() {
    Speaker::setAllOutput();
    LEDs::setAllOutput();

    Song<songSize> song;
    fillSong(song);

    EntenPlayer::playSong(song);
}

void fillSong(Song<songSize> &song) {
    song.addNote(Note::c, NoteLength::achtel);
    song.addNote(Note::d, NoteLength::achtel);
    song.addNote(Note::e, NoteLength::achtel);
    song.addNote(Note::f, NoteLength::achtel);
    song.addNote(Note::g, NoteLength::viertel);
    song.addNote(Note::g, NoteLength::viertel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::g, NoteLength::viertel);
    song.addNote(Note::pause, NoteLength::viertel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::a, NoteLength::achtel);
    song.addNote(Note::g, NoteLength::viertel);
    song.addNote(Note::pause, NoteLength::viertel);
    song.addNote(Note::f, NoteLength::achtel);
    song.addNote(Note::f, NoteLength::achtel);
    song.addNote(Note::f, NoteLength::achtel);
    song.addNote(Note::f, NoteLength::achtel);
    song.addNote(Note::e, NoteLength::viertel);
    song.addNote(Note::e, NoteLength::viertel);
    song.addNote(Note::g, NoteLength::achtel);
    song.addNote(Note::g, NoteLength::achtel);
    song.addNote(Note::g, NoteLength::achtel);
    song.addNote(Note::g, NoteLength::achtel);
    song.addNote(Note::c, NoteLength::viertel);

    song.addNote(Note::pause, NoteLength::ganz);
};