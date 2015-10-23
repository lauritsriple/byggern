/*
 * game.h
 *
 * Created: 23.10.2015 15:19:03
 *  Author: shahrukk
 */ 

#include <avr/io.h>

#ifndef GAME_H_
#define GAME_H_


uint16_t game_getScore(void);
void game_addPoints(void);
void game_timerStart(void);
void game_timerStop(void);


#endif /* GAME_H_ */