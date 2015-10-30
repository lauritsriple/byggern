/*
 * ATmega162.c
 *
 * Created: 28.08.2015 12:04:28
 *  Author: laurittr
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "communication/uart.h"
#include "sram/SRAM_test.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "analog/adc.h"
#include "analog/joy.h"
#include "display/oled.h"
#include "communication/can.h"
#include "communication/mcp2515defines.h"
#include "communication/mcp2515.h"


#define LED 0
#define SW1 1

ISR(INT2_vect){
	adc_conversion = 0;
}



int main(void) {
	DDRB |= (1 << PB0);
	DDRB &= ~(1 << PB1);
	DDRB &= ~(1 << PB2);
	MCUCR |= (1 << SRE);
	uart_init();
	printf("\f");
	puts("UART\t\t initialized\r");
	adc_init();
	puts("ADC\t\t initialized\r");
	sei();
	puts("Interrupts\t enabled\r");				
	joy_init();
	puts("Joystick\t initialized\r");
	//oled_init();
	puts("OLED\t\t initialized\r");
	can_init(MODE_NORMAL);
	puts("SPI\t\t initialized");
	puts("MCP2515\t\t initialized");
	
	can_message_t* msg = malloc(sizeof(can_message_t));

	while(1) {
		PORTB ^= (1 << LED);
		//TODO: add this print as function in joy.c
		//printf("adc1: %i, adc2: %i, adc3: %i, adc4: %i\n", adc_read(0b00000100),adc_read(0b00000101), adc_read(0b00000110), adc_read(0b00000111));
		joy_pos_t pos = joy_getPos();
		//printf("X:%4i Y:%4i\r",pos.x,pos.y);
		//oled_printf("Shahrukh Er Best");
		msg->id=5;
		msg->length=4;
		msg->data[0]=pos.x>>8;
		msg->data[1]=pos.x;
		msg->data[2]=pos.y>>8;
		msg->data[3]=pos.y;
		//printf("sending:  ");
		//can_print(*msg);
		can_messageSend(msg,MCP_TXB1CTRL);
    }
}



//LEFT TOUCH = PORT B, PIN 5 AND PIN 6
//RIGHT TOUCH = PORT D, PIN 1 AND PIN 2

//WE GET AT SMOOTHER SIGNAL AFTER PWM