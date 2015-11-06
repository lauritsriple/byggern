/*
 * pwm.c
 *
 * Created: 06.11.2015 11:59:20
 *  Author: laurittr
 */ 



#include "pwm.h"
#include <avr/io.h>

void pwm_init(void){
	TCCR0A |= (1 << COM0A1); //Non inverting 
	TCCR0A |= (1 << WGM00) | (1 << WGM01); //Fast pwm
	TCCR0B |= (1 << CS01); // prescalet to 8
}

void pwm_set(uint8_t ch,uint8_t val){
	switch (ch){
		case 1:
			OCR0A=val;
			break;
		case 2:
			OCR0B=val;
			break;
		default:
			break;
	}
}