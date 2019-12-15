/*
 * mySPI.h
 *
 *  Created on: Oct 10, 2019
 *      Author: Andi
 */

#ifndef MYSPI_MYSPI_H_
#define MYSPI_MYSPI_H_

#include <avr/io.h>
#include <stdio.h>

#define DDR_SPI DDRB
#define DD_SS	DDB2
#define DD_SCK	DDB5
#define DD_MOSI DDB3
#define DD_MISO DDB4
#define PORT_SPI PORTB

void SPI_MasterInit(void);
char SPI_MasterTransmit(char cData);
char SPI_MasterStr(char *text);

#endif /* MYSPI_MYSPI_H_ */
