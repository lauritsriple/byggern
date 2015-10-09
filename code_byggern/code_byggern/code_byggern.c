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
#include "mcp2515.h"


#define LED 0
#define SW1 1



ISR(INT2_vect){
	adc_conversion = 0;
}

void can_print(can_message_t m){
	printf("can_message_t(id:%d, len:%d, data:{", m.id, m.length);
	if(m.length){
		printf("%d", m.data[0]);
	}
	for(uint8_t i = 1; i < m.length; i++){
		printf(", %d", m.data[i]);
	}
	printf("})\n");	
}

int main(void) {
	DDRB |= (1 << PB0);
	DDRB &= ~(1 << PB1);
	DDRB &= ~(1 << PB2);
	MCUCR |= (1 << SRE);
	uart_init();
	//printf("\f");
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
	
	can_message_t* msg = malloc(sizeof(can_message_t));

	//mcp2515_bitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);

	printf("CANSTAT: 0x%02x\n", mcp2515_read(MCP_CANSTAT));
	printf("CANCTRL: 0x%02x (should be 0x47)\n", mcp2515_read(MCP_CANCTRL));

	while(1) {
		PORTB ^= (1 << LED);
		//printf("adc1: %i, adc2: %i, adc3: %i, adc4: %i\n", adc_read(0b00000100),adc_read(0b00000101), adc_read(0b00000110), adc_read(0b00000111));
		//joy_pos_t pos = joy_getPos();
		//printf("X:%4i Y:%4i\r",pos.x,pos.y);
		//oled_printf("Shahrukh Er Best");
		
		msg->id=5;
		msg->length=2;
		msg->data[0]=0b11110000;
		msg->data[1]=0b00001111;
		printf("sending:  ");
		can_print(*msg);
		can_messageSend(msg,MCP_TXB0CTRL);
		
		_delay_ms(100);
		can_message_t receive = can_dataReceive();
		printf("received: ");
		can_print(receive);
		_delay_ms(100);
		
		//spi_write(0b00000010);
		//printf("test: %i\n",spi_read());
		
		_delay_ms(50);
    }
}



//LEFT TOUCH = PORT B, PIN 5 AND PIN 6
//RIGHT TOUCH = PORT D, PIN 1 AND PIN 2

//WE GET AT SMOOTHER SIGNAL AFTER PWM