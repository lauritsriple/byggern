/*
 * uart.c
 *
 * Created: 28.08.2015 12:14:48
 *  Author: laurittr
 */ 

#include <avr/io.h>
#include "uart.h"
#include <stdio.h>

#define F_CPU 16000000
#define ubrr (F_CPU/16/9600 - 1)

void uart_init(void){
	UBRR0L = (unsigned char) ubrr;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	UCSR0C |= (1<<UCSZ00);
	
	//for puts and printf
	fdevopen(uart_putChar, uart_getChar);
}


void uart_putChar(unsigned char c){
	while (!(UCSR0A & (1<<UDRE0))); //Wait for empty transmit buffer
	UDR0 = c; // Put data in to buffer
}


unsigned char uart_getChar(){
	
	while((UCSR0A) & (1<<RXC0)); //Wait for "full" transmit buffer
	return UDR0;
}

