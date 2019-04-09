#include <avr/io.h>

#include <UART.h>

constexpr int MOSI = 5;
constexpr int SCK = 7;
constexpr int MISO = 6;

void SPI_MasterInit() {
/* Set MOSI and SCK output, all others input */
    DDRB = (1 << MOSI) | (1 << SCK);
/* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(uint8_t cData) {
/* Start transmission */
    SPDR = cData;
/* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)));
}

void SPI_SlaveInit() {
/* Set MISO output, all others input */
    DDRB = (1 << MISO);
/* Enable SPI */
    SPCR = (1 << SPE);
}

char SPI_SlaveReceive() {
/* Wait for reception complete */
    while (!(SPSR & (1 << SPIF)));
/* Return data register */
    return SPDR;
}

int main() {
    UART::enableSync();
    UART::setBaud(9600);

    DDRC = 0xff;

    SPI_MasterInit();
    SPI_MasterTransmit(8);

    SPI_SlaveInit();
    const uint8_t value = SPI_SlaveReceive();

    UART::writeByte(value);
    PORTC = ~value;

    while (true);
}