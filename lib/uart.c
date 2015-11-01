/*
 * uart.c
 *
 * Created: 28.08.2015 12:14:48
 *  Author: laurittr
 */ 

#include <avr/io.h>
#include "uart.h"
#include <stdio.h>

#define ubrr (F_CPU/16/BAUD - 1)

void uart_init(void){
	UBRR0L = (unsigned char) ubrr;
	//UBRR0L = 15;	// baudrate 192000hz
	//UBRR0L = 0b00001111; //atmega162
	
	UCSR0B |= (1 << RXEN0)	//recieve enable
			| (1 << TXEN0);	//transmit enable
	
	#if defined(__AVR_ATmega162_)
		USCSR0C |= ( 1 << URSEL0)
				| ( 1 << UCSZ00); //char size to 8bit
	#elif defined(__AVR_ATmega2560__)
		UCSR0C |= (3 << UCSZ00); // char size to 8
	#endif

	//for puts and printf
	fdevopen(uart_putChar, uart_getChar);
}


void uart_putChar(unsigned char c){
	while (!(UCSR0A & (1<<UDRE0))); //Wait for empty transmit buffer
	UDR0 = c; // Put data in to buffer
}


unsigned char uart_getChar(){
	while(!((UCSR0A) & (1<<RXC0))); //Wait for "full" transmit buffer
	return UDR0;
}

