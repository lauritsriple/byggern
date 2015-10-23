/*
 * pwm.c
 *
 * Created: 23.10.2015 08:57:32
 *  Author: shahrukk
 */ 

#include "pwm.h"
#include <avr/interrupt.h>
#include <avr/io.h>


void pwm_init(void){
	//fast pwm
	TCCR3A &= ~(1<< WGM30);
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM32);
	TCCR3B |= (1<<WGM33);
	
	//inverting
	TCCR3A|= (1<<COM3A0);
	TCCR3A|= (1<<COM3A1);
	
	//prescaler
	TCCR3B |= (1<<CS30) | (1<<CS32);
	TCCR3B&= ~(1<<CS31);
	
	ICR3 = 312;
}

//val is inverted.
void pwm_setValue(uint8_t val){
	if ((val>=24) && (val<=42)){
		OCR3AL=val;
	}
	else{
		OCR3AL=33;
	}
}


