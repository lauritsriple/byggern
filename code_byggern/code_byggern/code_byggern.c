/*
 * code_byggern.c
 *
 * Created: 28.08.2015 12:04:28
 *  Author: laurittr
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>
#include "uart.h"




int main(void) {
	uart_init();
	
	DDRB |= (1 << PB0);
    while(1) {
		PORTB ^= (1 << PB0);
        uart_putChar(F);
		_delay_ms(50);
    }
}