/*
 * ATmega162.c
 *
 * Created: 28.08.2015 12:04:28
 *  Author: laurittr
 */ 

//#define F_CPU 4915200 //defined in toolchain

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "analog/adc.h"
#include "../lib/uart.h"
#include "sram/SRAM_test.h"
#include "../lib/joy.h"
#include "display/oled.h"
#include "../lib/can.h"
#include "../lib/mcp2515defines.h"
#include "../lib/mcp2515.h"
#include "board.h"

int main(void) {
	//DDRB |= (1 << PB0); Moved to board.h
	//DDRB &= ~(1 << PB1);
	//DDRB &= ~(1 << PB2); //RX, uart as input? Is it really needed? SHOULD BE TESTED?
	board_init();
	uart_init();
	puts("Board\t\t initialized\r");
	//printf("\f"); What is this for?
	puts("UART\t\t initialized\r");
	
	adc_init();
	puts("ADC\t\t initialized\r");
		
	//oled_init();
	//puts("OLED\t\t initialized\r");
	
	can_init(MODE_NORMAL);
	puts("SPI\t\t initialized\r");
	puts("MCP2515\t\t initialized\r");
	puts("CAN\t\t initialized\r");
	
	sei();
	puts("Interrupts\t enabled\r");
	
	joy_init();
	puts("Joystick\t initialized\r");
		
	can_message_t* msg = malloc(sizeof(can_message_t));
	can_message_t receive;
	
	while(1) {
		uint8_t adcRead=0;
		LED_PORT ^= (1 << LED1);
		//SRAM_testADC();
		//TODO: add this print as function in joy.c
		//printf("adc1: %i, adc2: %i, adc3: %i, adc4: %i\n", adc_read(0b00000100),adc_read(0b00000101), adc_read(0b00000110), adc_read(0b00000111));
		//joy_pos_t pos = joy_getPos();
		//printf("X:%4i Y:%4i\r",pos.x,pos.y);
		receive = can_dataReceive();
		switch(receive.id){
			case 50: ;//sram test
				uint8_t* test = SRAM_test();
				msg->id=51; //sram test complete
				msg->length=2;
				msg->data[0]=test[0];
				msg->data[1]=test[1];
				can_messageSend(msg,MCP_TXB1CTRL);
				break;
			case 101: //read joy set adcreadmode
				adcRead=1; //game AT162 read joystick
				
			case 7:
				adcRead=0; //game over
				
			case 2050:
				printf("invalid message or no message\n");
				break;
			
			default:
				break;
		} 
		
		if (adcRead){
			joy_pos_t pos = joy_getPos();
			msg->id=121; //joy id
			msg->length=4;
			msg->data[0]=pos.x>>8;
			msg->data[1]=pos.x;
			msg->data[2]=pos.y>>8;
			msg->data[3]=pos.y;
			can_messageSend(msg,MCP_TXB1CTRL);
		}
		
		/*msg->data[0]=pos.x>>8;
		msg->data[1]=pos.x;
		msg->data[2]=pos.y>>8;
		msg->data[3]=pos.y;*/
		
		//printf("sending:  ");
		//can_print(*msg);
		//can_messageSend(msg,MCP_TXB1CTRL);
		printf("received: ");
		receive=can_dataReceive();
		can_print(receive);
		_delay_ms(100);
    }	
}