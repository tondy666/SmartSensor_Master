/*
 * main.c
 *
 *  Created on: Sep 13, 2019
 *      Author: Andi
 */

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <avr/io.h>
#include <util/delay.h>

#include "myUART/myUART.h"
#include "mySPI/mySPI.h"

#define dummyGround 	PD7
#define button			PD4

/* variable analogRaw	*/
uint8_t sHigh0=0, sLow0=0;
uint8_t sHigh1=0, sLow1=0;
uint8_t sHigh2=0, sLow2=0;
uint16_t sFull0=0, sFull1=0, sFull2=0;

/* variable calibrate	*/
uint8_t tHigh0=0, tLow0=0;
uint8_t tHigh1=0, tLow1=0;
uint8_t tHigh2=0, tLow2=0;
uint16_t tFull0=0, tFull1=0, tFull2=0;

/* variable digitalRaw	*/
uint8_t digital;

/* variable autocalibrate	*/
uint8_t autoCal;

/* variable calibrateall	*/
uint8_t allCal;

uint8_t debounce=0xFF;

enum state{analogRaw, digitalRaw, calibrateAll, calibrateS0, calibrateS1, calibrateS2, calibrateAuto, decision, }myState;

uint8_t buttonPressed(void);
void print_analogRaw(void);
void print_digitalRaw(void);
void print_calibrateS0(void);
void print_calibrateS1(void);
void print_calibrateS2(void);
void print_calibrateAll(void);
void print_calibrateAuto(void);
void print_decision(void);


int main(void) {
	/* Initializing all functions	*/
	USART_Init();
	SPI_MasterInit();

	/* make PD7 as dummy ground	*/
	DDRD |= (1<<dummyGround);
	PORTD &= ~(1<<dummyGround);
	//	DDRB |= (1<<led);	//PB5 as output

	/* Make PD4 as input button	*/
	DDRD &= ~(1<<button);
	PORTD |= (1<<button);	//pullup enable
	while (1) {

		switch(myState){
		case analogRaw:{
			USART_PutStr("analogRaw: ");
			print_analogRaw();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = digitalRaw;
		}break;

		case digitalRaw:{
			USART_PutStr("digitalRaw: ");
			print_digitalRaw();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = calibrateS0;
		}break;

		case calibrateS0:{
			USART_PutStr("calibrateS0: ");
			print_calibrateS0();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = calibrateS1;
		}break;

		case calibrateS1:{
			USART_PutStr("calibrateS1: ");
			print_calibrateS1();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = calibrateS2;
		}break;

		case calibrateS2:{
			USART_PutStr("calibrateS2: ");
			print_calibrateS2();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = calibrateAll;
		}break;

		case calibrateAll:{
			USART_PutStr("calibrateAll: ");
			print_calibrateAll();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = calibrateAuto;
		}break;

		case calibrateAuto:{
			USART_PutStr("calibrateAuto: ");
			print_calibrateAuto();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = decision;
		}break;

		case decision:{
			USART_PutStr("decision: ");
			print_decision();
			USART_PutStr("\n");
			if(buttonPressed())
				myState = analogRaw;
		}break;
		}
	}
}

void print_analogRaw(void){
	SPI_MasterTransmit(0x01);
	_delay_us(500);
	sLow0 = SPI_MasterTransmit(0x02);
	_delay_us(500);
	sHigh0 = SPI_MasterTransmit(0x03);
	_delay_us(500);
	sLow1 = SPI_MasterTransmit(0x04);
	_delay_us(500);
	sHigh1 = SPI_MasterTransmit(0x05);
	_delay_us(500);
	sLow2 = SPI_MasterTransmit(0x06);
	_delay_us(500);
	sHigh2 = SPI_MasterTransmit(0x00);
	_delay_us(500);


	sFull0 = (sHigh0 << 8) | sLow0;
	sFull1 = (sHigh1 << 8) | sLow1;
	sFull2 = (sHigh2 << 8) | sLow2;

	USART_PutNum(sHigh0); USART_PutStr("^"); USART_PutNum(sLow0); USART_PutStr("^"); USART_PutNum(sFull0);
	USART_PutStr(" - ");
	USART_PutNum(sHigh1); USART_PutStr("^"); USART_PutNum(sLow1); USART_PutStr("^"); USART_PutNum(sFull1);
	USART_PutStr(" - ");
	USART_PutNum(sHigh2); USART_PutStr("^"); USART_PutNum(sLow2); USART_PutStr("^"); USART_PutNum(sFull2);
}
void print_digitalRaw(void){
	digital = SPI_MasterTransmit(0x0F);
	_delay_us(500);
	USART_PutNum(digital);
}
void print_calibrateS0(void){
	/* call data	*/
	SPI_MasterTransmit(0x07);
	_delay_us(500);
	tLow0 = SPI_MasterTransmit(0x08);
	_delay_us(500);
	tHigh0 = SPI_MasterTransmit(0x00);
	_delay_us(500);

	/* merge to 10 bit	*/
	tFull0 = (tHigh0 << 8) | tLow0;

	/* print data	*/
	USART_PutNum(tHigh0); USART_PutStr("^"); USART_PutNum(tLow0); USART_PutStr("^"); USART_PutNum(tFull0);

}
void print_calibrateS1(void){
	/* call data	*/
	SPI_MasterTransmit(0x09);
	_delay_us(500);
	tLow1 = SPI_MasterTransmit(0x0A);
	_delay_us(500);
	tHigh1 = SPI_MasterTransmit(0x00);
	_delay_us(500);

	/* merge to 10 bit	*/
	tFull1 = (tHigh1 << 8) | tLow1;

	/* print data	*/
	USART_PutNum(tHigh1); USART_PutStr("^"); USART_PutNum(tLow1); USART_PutStr("^"); USART_PutNum(tFull1);

}
void print_calibrateS2(void){
	/* call data	*/
	SPI_MasterTransmit(0x0B);
	_delay_us(500);
	tLow2 = SPI_MasterTransmit(0x0C);
	_delay_us(500);
	tHigh2 = SPI_MasterTransmit(0x00);
	_delay_us(500);

	/* merge to 10 bit	*/
	tFull2 = (tHigh2 << 8) | tLow2;

	/* print data	*/
	USART_PutNum(tHigh2); USART_PutStr("^"); USART_PutNum(tLow2); USART_PutStr("^"); USART_PutNum(tFull2);
}
void print_calibrateAll(void){
	allCal = SPI_MasterTransmit(0x0D);
	_delay_us(500);
	USART_PutChar(allCal);
}
void print_calibrateAuto(void){
	autoCal = SPI_MasterTransmit(0x0E);
	_delay_us(500);
	USART_PutChar(autoCal);
}
void print_decision(void){
	digital = SPI_MasterTransmit(0x10);
	_delay_us(500);

	USART_PutChar(digital);
}

uint8_t buttonPressed(void){
	_Bool flagDetect=0;
	if((PIND&(1<<button))==0)
		debounce = (debounce<<1);
	else
		debounce = (debounce<<1)|1;

	if(debounce == 0x03)
		flagDetect = 1;

	return flagDetect;
}
