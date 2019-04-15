#include <Pins.h>

using Buttons = Pins<Port::A>;
using LEDs = Pins<Port::C>;

int main() {
    Buttons::setAllInput();
    LEDs::setAllOutput();

    while (true) {
        LEDs::writeMask(Buttons::readAllPins());
    }

}