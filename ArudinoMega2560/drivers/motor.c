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
#include "../boardhack.h"

static void motor_enable (uint8_t enable){
	if (enable){
		MOTOR_PORT |= (1 << MOTOR_EN);
	} else {
		MOTOR_PORT &= ~(1 << MOTOR_EN);
	}
}

static void motor_encoderOuptutEnable (uint8_t enable){
	if (enable){
		MOTOR_PORT &= ~(1 << MOTOR_ENCODER_EN);
		} else {
		MOTOR_PORT |= (1 << MOTOR_ENCODER_EN);
	}
}

void motor_encoderCounterReset(void){
	MOTOR_PORT &= ~(1<<MOTOR_ENCODER_RESET);
	_delay_us(20);
	MOTOR_PORT |= (1 <<MOTOR_ENCODER_RESET);
}

typedef enum encoderByte encoderByte;
enum encoderByte {EB_HIGH,EB_LOW};
	
static void motor_encoderSelectByte(encoderByte e){
	if (e==EB_HIGH){
		MOTOR_PORT |= (1 << MOTOR_ENCODER_SEL);
	}
	else{ //EB_LOW
		MOTOR_PORT &= ~(1 << MOTOR_ENCODER_SEL);
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
	MOTOR_DDR |= (1<<MOTOR_ENCODER_RESET) | (1<<MOTOR_ENCODER_EN) | (1<<MOTOR_ENCODER_SEL) | (1<<MOTOR_EN) | (1<<MOTOR_DIR);
	ENCODER_PORT=0;
	motor_encoderOuptutEnable(1);
	motor_encoderCounterReset();
	motor_encoderSelectByte(EB_HIGH);
	motor_encoderOuptutEnable(0);
	motor_enable(1);
}

void motor_direction(motorDirection dir){
	if (dir==right){
		MOTOR_PORT |= (1 << MOTOR_DIR);
	}
	else{ //left
		MOTOR_PORT &= ~(1 << MOTOR_DIR);
	}
}

void motor_speed(uint8_t speed){
	max520_send(speed);
}

int16_t motor_encoderRead(void){
	motor_encoderOuptutEnable(1);
	motor_encoderSelectByte(EB_HIGH);
	uint8_t msb = reverse_bits(ENCODER_PIN);
	motor_encoderSelectByte(EB_LOW);
	uint8_t lsb = reverse_bits(ENCODER_PIN);
	motor_encoderOuptutEnable(0); 
	//2s komplement
	return -((msb << 8) | lsb);
}

	
	





