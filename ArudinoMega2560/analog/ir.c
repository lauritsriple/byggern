/*
 * ir.c
 *
 * Created: 23.10.2015 15:12:56
 *  Author: shahrukk
 */ 

#include <stdint.h>
#include "adc.h"
#include "ir.h"
#include "../board.h"

uint8_t ir_signal(void){
	uint16_t value = adc_read(IR_CHANNEL);
	if (value > 900){
		return 1;
	}
	return 0;
}
