/*
 * code_byggern.c
 *
 * Created: 28.08.2015 12:04:28
 *  Author: laurittr
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <stdio.h>



int main(void) {
	uart_init();
	
	DDRB |= (1 << PB0);
    while(1) {
		PORTB ^= (1 << PB0);
        uart_putChar('f');
		puts("ho");
		printf("test int: %i", 100);
		_delay_ms(500);
    }
}