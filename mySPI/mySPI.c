#include <avr/io.h>
#include <stdint.h>
#include <ctype.h>
#include "mySPI.h"

void SPI_MasterInit(void) {
	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK);
	DDR_SPI &=~(1<<DD_MISO);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	SPSR &= ~(1<<SPI2X);
}


char SPI_MasterTransmit(char cData) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)));
	return SPDR;

}

char SPI_MasterStr(char *text){
	while(*text){
		SPI_MasterTransmit(*text++);
	}
	return SPDR;
}
