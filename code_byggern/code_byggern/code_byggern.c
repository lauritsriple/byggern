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
#include <stdio.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "joy.h"
#include "oled.h"
#include "gui.h"

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
	oled_init();
	puts("Oled initialized\r");
	
	char *c1 = "item1";
	char *c2 = "item2";
	char *c[2] = {c1,c2};
	gui_item_t current=gui_createMenu(NULL,c);
	current = gui_createMenu(&current.next,c);
	
	
	oled_home();
	while(1) {
		
		//oled_clear_all();
		if ((PINB &(1<<SW1))){
			PORTB ^= (1 << LED);	
		}
		PORTB ^= (1 << LED);
		//printf("adc1: %i, adc2: %i, adc3: %i, adc4: %i\n", adc_read(0b00000100),adc_read(0b00000101), adc_read(0b00000110), adc_read(0b00000111));
		//joy_pos_t pos = joy_getPos();
		//printf("X:%4i Y:%4i\r",pos.x,pos.y);
		//oled_printf("Shahrukh Er Best");
		
		_delay_ms(50);
    }
}



//LEFT TOUCH = PORT B, PIN 5 AND PIN 6
//RIGHT TOUCH = PORT D, PIN 1 AND PIN 2

//WE GET AT SMOOTHER SIGNAL AFTER PWM