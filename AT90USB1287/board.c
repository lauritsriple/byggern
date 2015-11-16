/*
 * board.c
 *
 * Created: 01.11.2015 15.15.18
 *  Author: laura
 */ 

#include "board.h"

/*void static init_sram(void){
	//MCUCR |= (1 << SRE); //Enables external memory interface
	//This will activate RD-PD7 and WR-PD6
	//Needed to interface oled on AT90USB1287
}*/

void board_init(void){
	LED_DDR |= (1 << LED1);
	SPI_DDR |= (1<<SPI_CS_MCP2515);

	//ADC_DDR &=~(1<<ADC_JOY_X);
	//ADC_DDR &=~(1<<ADC_JOY_Y);
}