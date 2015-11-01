/*
 * board.c
 *
 * Created: 01.11.2015 15.15.18
 *  Author: laura
 */ 

#include "board.h"

void static init_buttons(void){
	SW_DDR &= (1 << SW1);
}

void static init_leds(void){
	SW_DDR |= (1 << LED1);
}

/*void static init_sram(void){
	//MCUCR |= (1 << SRE); //Enables external memory interface
	//This will activate RD-PD7 and WR-PD6
}*/

void board_init(void){
	init_buttons();
	init_leds();
}