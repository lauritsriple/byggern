/*
 * adc.c
 *
 * Created: 23.10.2015 14:20:49
 *  Author: shahrukk
 */ 
#include <avr/io.h>
#include "adc.h"

void adc_init(void){
	ADCSRA |= (1 << ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1 << ADPS2); 
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 <<REFS1);
	
}

uint16_t adc_read(uint8_t ch){
	ADMUX |= (ch & 0x03);
	ADCSRA |= (1 << ADSC);
	
	while(!(ADCSRA & ADSC)){ 
		//Do nothing
	}
	uint16_t result; 
	result = ADCL | (ADCH << 8); 
	return result;
}


