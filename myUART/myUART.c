/*
 * myUART.c
 *
 *  Created on: Oct 10, 2019
 *      Author: Andi
 */
#include "myUART.h"
#include "stdio.h"

void USART_Init(void){
	//Setup baudrate
	UBRR0H = BAUDH;
	UBRR0L = BAUDL;

	//Enable Receiver & Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

	//Set frame format
	UCSR0C = (0 << USBS0) | (3 << UCSZ00);
}
volatile unsigned char USART_GetChar(void){
	//Wait for data for to be received
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
void USART_PutChar(unsigned char data){
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}
void USART_PutStr(char *text){
	while(*text){
		USART_PutChar(*text++);
	}
}
void USART_PutNum(int16_t number){
	char buff[20];
	sprintf(buff,"%d",number);
	USART_PutStr(buff);
}

