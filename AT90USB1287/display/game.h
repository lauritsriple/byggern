/*
 * game.h
 *
 * Created: 19.11.2015 19:19:04
 *  Author: laurittr
 */ 


#ifndef GAME_H_
#define GAME_H_
#include "can.h"
#include <stdint.h>

void highscoreSwap(uint16_t* a, uint16_t* b);
void game_start(void);
void game_end(can_message_t* endMsg);

#endif /* GAME_H_ */