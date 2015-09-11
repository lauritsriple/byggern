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
#include <avr/interrupt.h>
#include "ADC.h"
#include "joy.h"



ISR(INT2_vect){
	adc_conversion = 0;
}

int main(void) {
	adc_init();
	sei();
	uart_init();
	joy_calibrate();
								
	DDRB |= (1 << PB0);
	DDRB &= ~(1 << PB1);
	DDRB &= ~(1 << PB2);
	MCUCR |= (1 << SRE);
	
	
	
	
	
    while(1) {
		
		/*if ((PINB &(1<<PB1))){
			PORTB ^= (1 << PB0);	
		}*/
		
		PORTB ^= (1 << PB0);
		//printf("adc1: %i, adc2: %i, adc3: %i, adc4: %i\n", adc_read(0b00000100),adc_read(0b00000101), adc_read(0b00000110), adc_read(0b00000111));
		joy_pos_t pos = joy_getPos();
		printf("X:%4i y:%4i\n",pos.x,pos.y);
		//uart_putChar('f');
		//puts("ho");
		//printf("test int: %i", count);
		_delay_ms(50);
    }
}



//LEFT TOUCH = PORT B, PIN 5 AND PIN 6
//RIGHT TOUCH = PORT D, PIN 1 AND PIN 2

//WE GET AT SMOOTHER SIGNAL AFTER PWM