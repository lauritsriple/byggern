/*
 * game.c
 *
 * Created: 23.10.2015 15:18:49
 *  Author: shahrukk
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "game.h"

static volatile uint16_t score = 0;

uint16_t game_getScore(void){
	return score;
}

void game_addPoints(void){
	score= score+5;
}

void game_timerStart(void){
	score = 0;
	TCCR1B |=  (1 << CS10); 
	TIMSK1 |= (1 << TOIE1);
}

void game_timerStop(void){
	TCCR1B &= ~(1 << CS10);
	TIMSK1 &= ~(1 << TOIE1);
}

ISR(TIMER1_OVF_vect){
	game_addPoints();
}

//bruker ingen prescaler!!

