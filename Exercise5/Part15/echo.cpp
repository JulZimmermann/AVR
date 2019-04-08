#include <UART.h>

int main() {
    UART uart(9600);

    while (true) {
        uint8_t byte = uart.readByte();

        uart.writeByte(byte);
    }

}