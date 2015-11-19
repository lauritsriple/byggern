/*
 * ir.c
 *
 * Created: 23.10.2015 15:12:56
 *  Author: shahrukk
 */ 

#include <stdint.h>
#include "adc.h"
#include "ir.h"
#include "../boardhack.h"

uint8_t ir_signal(void){
	uint16_t value = adc_read8(IR_CHANNEL);
	if (value > 700){
		return 1;
	}
	return 0;
}
