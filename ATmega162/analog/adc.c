/*
 * ADC.c
 *
 * Created: 11.09.2015 13:17:03
 *  Author: shahrukk
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "../board.h"

volatile uint8_t adc_conversion;

void adc_init(void){
	GICR |= (1 << INT2); //interupt mask to enable the int2 vector
	EMCUCR &= ~(1 << ISC2); //rising edge interrupt
	ADC_DDR &= ~(1 << ADC_INT); //interupt pin as input
}


uint8_t adc_read(adc_ch ch){
		volatile char *adc_ram = (char *) 0x1400; // Start address for the ADC
		adc_ram[0] = (uint8_t)ch;
		adc_conversion = 1;
		//wait for adc to finish conversion, interrupt based
		while (adc_conversion){
			//do nothing, wait for interrupt
		}
		return adc_ram[0];
}

ISR(INT2_vect){ //INT2 = ADC_INT
	adc_conversion = 0;
}

