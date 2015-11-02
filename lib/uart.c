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
	#if defined (__AVR_AT90USB1287__)
		UBRR1L = (unsigned char) ubrr;
	#else
		UBRR0L = (unsigned char) ubrr;
	#endif
	//UBRR0L = 15;	// baudrate 192000hz
	//UBRR0L = 0b00001111; //atmega162
	
	#if defined(__AVR_AT90USB1287__)
		UCSR1B |= (1 << RXEN1)
		| (1 << TXEN1);
	#else
		UCSR0B |= (1 << RXEN0)	//recieve enable
		| (1 << TXEN0);	//transmit enable
	#endif

	
	#if defined(__AVR_ATmega162_)
		USCSR0C |= ( 1 << URSEL0)
				| ( 1 << UCSZ00); //char size to 8bit
	#elif defined(__AVR_ATmega2560__)
		UCSR0C |= (3 << UCSZ00); // char size to 8
	#elif defined(__AVR_AT90USB1287)
		UCSR1C |= (3 << UCSZ00);
	#endif
	

	//for puts and printf
	fdevopen(uart_putChar, uart_getChar);
}


void uart_putChar(unsigned char c){
	#if defined(__AVR_AT90USB1287__)
		while (!(UCSR1A & (1<<UDRE1))); //Wait for empty transmit buffer
		UDR1 = c; // Put data in to buffer
	#else
		while (!(UCSR0A & (1<<UDRE0))); //Wait for empty transmit buffer
		UDR0 = c; // Put data in to buffer
	#endif
}


unsigned char uart_getChar(){
	#if defined(__AVR_AT90USB1287__)
		while (!(UCSR1A & (1<<RXC1))); //Wait for "full" transmit buffer
		return UDR1;
	#else
		while (!(UCSR0A & (1<<UDRE0))); //Wait for "full" transmit buffer
		return UDR0;
	#endif
}

