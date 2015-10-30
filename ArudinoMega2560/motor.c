/*
 * motor.c
 *
 * Created: 30.10.2015 18:39:10
 *  Author: laurittr
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include "motor.h"
#include <stdint.h>
#include "communication/max520.h"

static void motor_enable (uint8_t enable){
	if (enable){
		PORTF |= (1 << PF4);
	} else {
		PORTF &= ~(1 << PF4);
	}
}

static void motor_encoderOuptutEnable (uint8_t enable){
	if (enable){
		PORTF &= ~(1 << PF7);
		} else {
		PORTF |= (1 << PF7);
	}
}

void motor_encoderCounterReset(void){
	PORTF &= ~(1<<PF6);
	_delay_us(20);
	PORTF |= (1 <<PF6);
}

typedef enum encoderByte encoderByte;
enum encoderByte {EB_HIGH,EB_LOW};
	
static void motor_encoderSelectByte(encoderByte e){
	if (e==EB_HIGH){
		PORTF |= (1 << PF5);
	}
	else{ //EB_LOW
		PORTF &= ~(1 << PF5);
	}
}

static uint8_t reverse_bits(uint8_t byte){
	byte = ((byte & 0b01010101) << 1) | ((byte & 0b10101010) >> 1);
	byte = ((byte & 0b00110011) << 2) | ((byte & 0b11001100) >> 2);
	byte = ((byte & 0b00001111) << 4) | ((byte & 0b11110000) >> 4);
	return byte;
}

void motor_init(void){
	max520_init();
	DDRF |= (1<<PF6) | (1<<PF7) | (1<<PF5) | (1<<PF4) | (1<<PF3);
	DDRK=0;
	motor_encoderOuptutEnable(1);
	motor_encoderCounterReset();
	motor_encoderSelectByte(EB_HIGH);
	motor_encoderOuptutEnable(0);
	motor_enable(1);
}

void motor_direction(motorDirection dir){
	if (dir==right){
		PORTF |= (1 << PF3);
	}
	else{ //left
		PORTF &= ~(1 << PF3);
	}
}

void motor_speed(uint8_t speed){
	max520_send(speed);
}

int16_t motor_encoderRead(void){
	motor_encoderOuptutEnable(1);
	motor_encoderSelectByte(EB_HIGH);
	uint8_t msb = reverse_bits(PINK);
	motor_encoderSelectByte(EB_LOW);
	uint8_t lsb = reverse_bits(PINK);
	motor_encoderOuptutEnable(0); 
	//2s komplement
	return -((msb << 8) | lsb);
}

	
	





