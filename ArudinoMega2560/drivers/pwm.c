/*
 * pwm.c
 *
 * Created: 23.10.2015 08:57:32
 *  Author: shahrukk
 */ 

#include "pwm.h"
//#include <avr/interrupt.h> Not needed?
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
	
	pwm_setValue(PWM_MID); //centre servo on init
}

void pwm_setValue(uint8_t val){
	OCR3AL=val;
}

//values between -100 and +100
void pwm_setServo(int16_t val){
	//transelate -100->+100 to values between 24 and 42
	val+=100;
	//now, we have 0-200; we want 0-18 and then + 21 so we have 21-39
	val=((val*18)/200)+PWM_MIN;

	if ((val<=(PWM_MID+1)) && (val>=(PWM_MID-1))){
		pwm_setValue(PWM_MID);
	}
	
	else if ((val>=PWM_MIN) && (val<=PWM_MAX)){
		pwm_setValue(val);
	}
	else{
		pwm_setValue(PWM_MID);
	}
}


