#include <UART.h>

int main() {
    UART::enableSync();
    UART::setBaud(9600);

    while (true) {
        const uint8_t byte = UART::readByte();
        UART::writeByte(byte);
    }

}
