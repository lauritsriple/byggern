/*
 * pwm.c
 *
 * Created: 23.10.2015 08:57:32
 *  Author: shahrukk
 */ 

#include "pwm.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "../communication/uart.h"

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

void pwm_setValue(uint8_t val){
	OCR3AL=val;
}

//values between -100 and +100
void pwm_setServo(int16_t val){
	static uint8_t max=39;
	static uint8_t min=21;
	uint8_t mid=(max+min)/2;
	
	//transelate -100->+100 to values between 24 and 42
	val+=100;
	//now, we have 0-200; we want 0-18 and then + 24
	val=((val*18)/200)+min;
		
	printf("val: %4i \n",val);
	
	if ((val<=(mid+1)) && (val>=(mid-1))){
		pwm_setValue(mid);
	}
	
	else if ((val>=min) && (val<=max)){
		pwm_setValue(val);
	}
	else{
		pwm_setValue(mid);
	}
}


