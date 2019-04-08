#include <avr/io.h>

#include <stddef.h>

#include <Pins.h>

#include <UART.h>

int main() {
    UART uart(9600);

    while (true) {
        uart.writeString("Hallo Welt\r\n");
    }

}