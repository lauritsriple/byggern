/*
 * ADC.c
 *
 * Created: 11.09.2015 13:17:03
 *  Author: shahrukk
 */ 

#include <avr/io.h>
#include "ADC.h"

void adc_init(void){
	GICR |= (1 << INT2);
	EMCUCR &= ~(1 << ISC2);
	DDRE &= ~(1 << PE0); 
}


uint8_t adc_read(adc_ch ch){
		puts("heree");
		volatile char *adc_ram = (char *) 0x1400; // Start address for the ADC
		puts("heree");
		adc_ram[0] = (uint8_t)ch;
		puts("heree");
		adc_conversion = 1;
		puts("heree");
		//wait for adc to finish conversion, interrupt based
		while (adc_conversion){
			//do nothing, wait for interrupt
		}
		puts("heree");
		return adc_ram[0];
}

