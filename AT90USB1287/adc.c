/*
 * adc.c
 *
 * Created: 06.11.2015 13:59:26
 *  Author: laurittr
 */ 

#include "adc.h"
#include <avr/io.h>

void adc_init(void){
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 <<REFS1);
	ADCSRA |= (1 << ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1 << ADPS2); 
}

void adc_reset(void){
	ADMUX &= ~(1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	ADCSRA &= ~((1<<ADEN) | (1 << ADPS0) | (1 <<ADPS1) | (1<<ADPS2));
}

uint16_t adc_read10(uint8_t ch){
	ADMUX = (ADMUX & 0xF8) | (ch & 0x03);
	ADCSRA |= (1 << ADSC);
	
	while((ADCSRA & (1<<ADSC))){
		//Do nothing
	}
	
	return ADC;
}

uint8_t adc_read8(uint8_t ch){
	return adc_read10(ch)>>2;
}