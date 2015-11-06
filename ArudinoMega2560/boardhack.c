/*
 * board.c
 *
 * Created: 01.11.2015 16.06.07
 *  Author: laura
 */ 


#include <avr/io.h>
#include "../ArudinoMega2560/boardhack.h"

void board_init_hack(void){
	LED_DDR |= (1 << LED1);
	PWM_DDR |= (1 << PWM1);
}