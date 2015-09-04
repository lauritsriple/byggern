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
#include "SRAM_test.h"
#include <stdio.h>




int main(void) {
	
	//Initialize uart and debugLED
	uart_init();									
	DDRB |= (1 << PB0);
	MCUCR |= (1 << SRE);
	
	SRAM_test();
    while(1) {
		PORTB ^= (1 << PB0);										//Toggle DebugLED
        
		//uart_putChar('f');
		//puts("ho");
		//printf("test int: %i", count);
		_delay_ms(500);
    }
}