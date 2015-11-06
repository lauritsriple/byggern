/*
 * board.c
 *
 * Created: 01.11.2015 15.15.18
 *  Author: laura
 */ 

#include "board.h"

void board_init(void){
	LED_DDR |= (1 << LED1); //Debug led
	MCUCR |= (1 << SRE); //Enables external memory interface
	//This will activate RD-PD7 and WR-PD6
}