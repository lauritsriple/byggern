/*
 * ir.c
 *
 * Created: 23.10.2015 15:12:56
 *  Author: shahrukk
 */ 

#include <avr/io.h>
#include "adc.h"
#include "ir.h"

uint8_t ir_signal(void){
	uint16_t value = adc_read(IRCHANNEL);
	if (value > 900){
		return 1;
	}
	return 0;
}
