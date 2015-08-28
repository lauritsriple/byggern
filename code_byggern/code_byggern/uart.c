/*
 * uart.c
 *
 * Created: 28.08.2015 12:14:48
 *  Author: laurittr
 */ 

#include <avr/io.h>
#include "uart.h"
#include <stdio.h>

void uart_init(void){
	//UBRR0L = 15;	// baudrate 192000hz
	UBRR0L = 0b00001111;
	
	//Asynchronous operation
	//UCSR0C &= ~(1 << UMSEL0);
	
	//Parity mode
	//UCSR0C &= ~((1 << UPM01)|(1 << UPM00));
	
	//Stopbit
	//UCSR0C &= ~(1 << USBS0);
	
	//Character size
	//UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	//UCSR0B &= ~(1 << UCSZ02);
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	//for puts and printf
	fdevopen(uart_putChar, uart_getChar);
}


void uart_putChar(unsigned char c){
	while (!(UCSR0A & (1<<UDRE0))); //Wait for empty transmit buffer
	UDR0 = c; // Put data in to buffer
}


unsigned char uart_getChar(){
	
	while((UCSR0A) & (1<<UDRE0)); //Wait for "full" transmit buffer
	return UDR0;
}

