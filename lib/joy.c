/*
 * joy.c
 *
 * Created: 11.09.2015 15:41:00
 *  Author: shahrukk
 */ 

#include "joy.h"
#include "adc.h"
#include <stdint.h>

#if defined (__AVR_AT90USB1287__)
#include "../AT90USB1287/board.h"
#elif defined(__AVR_ATmega2560__)
#include "../ArudinoMega2560/board.h"
#elif defined (__AVR_ATmega162__)
#include "../ATmega162/board.h"
#endif

static int16_t x_center;
static int16_t y_center;


void joy_init(){
	x_center=adc_read8(ADC_JOY_X);
	y_center=adc_read8(ADC_JOY_Y);
}

joy_pos_t joy_getPos(void){
	int16_t pos_x=adc_read8(ADC_JOY_X);
	int16_t pos_y=adc_read8(ADC_JOY_Y);
	pos_x-=x_center;
	pos_y-=y_center;
	pos_x=(pos_x*100)/127;
	pos_y=(pos_y*100)/127;
	if (pos_x>100){
		pos_x=100;
	}
	else if (pos_x<-100){
		pos_x=-100;
	}
	if (pos_y>100){
		pos_y=100;
	}
	else if (pos_y<-100){
		pos_y=-100;
	}
	joy_pos_t pos_tmp;
	pos_tmp.x=pos_x;
	pos_tmp.y=pos_y;
	return pos_tmp;
}

joy_pos_t joy_getPosRaw(void){
	int16_t pos_x=adc_read8(ADC_JOY_X);
	int16_t pos_y=adc_read8(ADC_JOY_Y);
	joy_pos_t pos_tmp;
	pos_tmp.x=pos_x;
	pos_tmp.y=pos_y;
	return pos_tmp;
}



