/*
 * code_byggern.c
 *
 * Created: 28.08.2015 12:04:28
 *  Author: laurittr
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>

int main(void) {
	DDRB |= (1 << PB0);
    while(1) {
		PORTB ^= (1 << PB0);
        //TODO:: Please write your application code 
		//comment for testcommit nothing really changed
		//one more
    }
}