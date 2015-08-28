/*
 * uart.c
 *
 * Created: 28.08.2015 12:14:48
 *  Author: laurittr
 */ 

//#include <avr/io.h>
#include "uart.h"

void uart_init(void){
	UBRRL = 15;	// baudrate 192000hz
	UCSRB |= (1 << RXEN0) | (1 << TXEN0);
	
	//Asynchronous operation
	UCSRC &= ~(1 << UMSEL0)
	
	//Parity mode
	USCRC &= ~((1 << UPM01)|(1 << UPM00))
	
	//Stopbit
	USCRC &= ~(1 << USBS0);
	
	//Character size
	USCRC |= (1 << UCSZ00) | (1 << UCSZ01);
	USCRC &= ~(1 << UCSZ02);
}

