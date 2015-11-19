/*
 * game.c
 *
 * Created: 19.11.2015 19:18:51
 *  Author: laurittr
 */ 

#include "can.h"
#include "touch.h"
#include "joy.h"
#include <stdint.h>
#include "avr/io.h"
#include "gui.h"

uint16_t static highscore[10];

void highscoreSwap(uint16_t* a, uint16_t* b){
	uint16_t tmp=*a;
	*a=*b;
	*b=tmp;
}

//Start game
/*
while
send start command to node3
send sensordata to node 3
if node3 detects ir will send msg on can to stop game.
call end game
*/

void game_start(void){
	gui_drawGameStart();
	uint8_t ls,rs,lb,rb;
	can_message_t receive;
	can_message_t * msg = malloc(sizeof(can_message_t));
	receive=can_dataReceive();
	msg->id=100; //game starter id
	msg->length=1;
	msg->data[0]=1;
	can_messageSend(msg);
	while (receive.id!=7){ //game ender id
		if (TOUCHMODE==1){
			touch_measure(&ls,&rs,&lb,&rb);
			msg->id=140; //touch id
			msg->length=4;
			msg->data[0]=255-ls;
			msg->data[1]=rs;
			msg->data[2]=lb;
			msg->data[3]=rb;
			can_messageSend(msg,MCP_TXB1CTRL);
		}
		else{
			joy_pos_t pos = joy_getPos();
			uint8_t btn=(!(SW_PIN & (1<<SW)));
			msg->id=120; //joy id
			msg->length=5;
			msg->data[0]=pos.x>>8;
			msg->data[1]=pos.x;
			msg->data[2]=pos.y>>8;
			msg->data[3]=pos.y;
			msg->data[4]=btn;
		}
		receive=can_dataReceive();
		gui_drawGame();
	}
	game_end(receive);
}


//end game
/*
save score in array,
print final score on screen,
print placement in higscorelist
*/ 
void game_end(can_message_t* endMsg){
	uint16_t score=(endMsg->data[0]<<8)|(endMsg->data[1]);
	for(uint8_t i = 9; i>=0;i--){
		if (score>=highscore[i]){
			highscoreSwap(score,highscore[i]);
		}
	}
	gui_drawGameEnd();
}