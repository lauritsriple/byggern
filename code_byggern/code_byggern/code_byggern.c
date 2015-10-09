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
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "joy.h"
#include "oled.h"
#include "can.h"
#include "mcp2515defines.h"


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
	puts("Uart initialized\r");
	adc_init();
	puts("ADC initialized\r");
	sei();
	puts("Global interrupts enabled\r");				
	joy_init();
	puts("Joystick initialized\r");
	//oled_init();
	puts("Oled initialized\r");
	can_init(MODE_LOOPBACK);
	
	uint8_t error=mcp2515_init();
	puts("Can controller, mcp2515, initialized\r");
	printf("error:%i\r\n",error);
	can_message_t* msg = malloc(sizeof(can_message_t));
	while(1) {
		PORTB ^= (1 << LED);
		//printf("adc1: %i, adc2: %i, adc3: %i, adc4: %i\n", adc_read(0b00000100),adc_read(0b00000101), adc_read(0b00000110), adc_read(0b00000111));
		//joy_pos_t pos = joy_getPos();
		//printf("X:%4i Y:%4i\r",pos.x,pos.y);
		//oled_printf("Shahrukh Er Best");
		
		can_message_t *receive;
		msg->id=0b1111000011110000;
		msg->length=2;
		msg->data[0]=0b11110000;
		msg->data[1]=0b00001111;
		can_messageSend(msg,MCP_TXB0CTRL);
		_delay_ms(100);
		can_dataReceive(MCP_RXB0CTRL, receive);
		printf("id: %i, data: %i %i \n ",receive->id,receive->data[0],receive->data[1]);
		_delay_ms(100);
		
		//spi_write(0b00000010);
		//printf("test: %i\n",spi_read());
		
		_delay_ms(50);
    }
}



//LEFT TOUCH = PORT B, PIN 5 AND PIN 6
//RIGHT TOUCH = PORT D, PIN 1 AND PIN 2

//WE GET AT SMOOTHER SIGNAL AFTER PWM