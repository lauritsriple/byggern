/*
 * game.c
 *
 * Created: 19.11.2015 19:18:51
 *  Author: laurittr
 */ 

#include "can.h"
#include "mcp2515defines.h"
#include "touch.h"
#include "joy.h"
#include <stdint.h>
#include "avr/io.h"
#include "display/gui.h"
#include "board.h"
#include <stdlib.h>
#include "game.h"

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
	uint8_t pressed=0;
	extern uint8_t touchMode;
	can_message_t receive;
	can_message_t * msg = malloc(sizeof(can_message_t));
	receive=can_dataReceive();
	if (touchMode==1){
		msg->id=100; //game starter id
		msg->length=1;
		msg->data[0]=1;
	}
	else {
		msg->id=101; //game starter id
		msg->length=1;
		msg->data[0]=1;
	}

	can_messageSend(msg,MCP_TXB1CTRL);
	while (receive.id!=7){ //game ender id
		if (touchMode==1){
			touch_measure(&ls,&rs,&lb,&rb);
			msg->id=140; //touch id
			msg->length=4;
			msg->data[0]=255-ls;
			msg->data[1]=rs;

			if ((lb==1) && (pressed==1)){
				msg->data[2]=0;
			}
			else if ((lb==0) && (pressed==1)){
				msg->data[2]=0;
				pressed=0;
			}
			else if ((lb==1) && (pressed==0)){
				msg->data[2]=lb;
				pressed=1;
			}
			else { //lb=0,pressed=0
				msg->data[2]=0;
			}
			printf("solenoid: %i lb: %i\n",msg->data[2],lb);
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
			can_messageSend(msg,MCP_TXB1CTRL);
		}
		receive=can_dataReceive();
		uint16_t score=0;
		if (receive.id==8){  //score id
			score=(receive.data[0]<<8)|(receive.data[1]);
			gui_drawGame(score);
		}
		if (!(SW_PIN & (1<<SW2))){
			msg->id=250; //force quit
			msg->length=1;
			msg->data[0]=0;
			can_messageSend(msg,MCP_TXB1CTRL);
			break;	
		}
		if (receive.id==7){
			game_end(receive);
			break;
		}
	}

	
}

void game_startAT(void){
	gui_drawGameStart();
	uint8_t pressed=0;
	can_message_t receive;
	can_message_t * msg = malloc(sizeof(can_message_t));
	receive=can_dataReceive();
	msg->id=101; //game starterAT162 id
	msg->length=1;
	msg->data[0]=1;
	can_messageSend(msg,MCP_TXB1CTRL);
	while (receive.id!=7){ //game ender id
		receive=can_dataReceive();
		uint8_t btn=(!(SW_PIN & (1<<SW)));
		msg->id=122; //btn id
		msg->length=1;
		if ((btn==1) && (pressed==1)){
			msg->data[0]=0;
		}
		else if ((btn==0) && (pressed==1)){
			msg->data[0]=0;
			pressed=0;
		}
		else if ((btn==1) && (pressed==0)){
			msg->data[0]=btn;
			pressed=1;
		}
		else { //lb=0,pressed=0
			msg->data[0]=0;
		}
		can_messageSend(msg,MCP_TXB1CTRL);
		uint16_t score=0;
		if (receive.id==8){  //score id
			score=(receive.data[0]<<8)|(receive.data[1]);
			gui_drawGame(score);
		}
	}
	game_end(receive);
}

void game_AT(void){
	can_message_t receive;
	while(SW_PIN & (1<<SW2)){
		receive=can_dataReceive();
		if (receive.id==121){
			joy_pos_t pos = joy_getPos();
			pos.x = receive.data[0]<<8 | receive.data[1];
			pos.y = receive.data[2]<<8 | receive.data[3];
			printf("pos:%i,pos:%i\n",pos.x,pos.y);
			gui_clearAll();
			gui_putString(30,2,"Joy X: %i",pos.x);
			gui_putString(30,3,"Joy Y: %i",pos.y);
			gui_update();
		}
		
	}
	
}


//end game
/*
save score in array,
print final score on screen,
print placement in higscorelist
*/ 
void game_end(can_message_t endMsg){
	uint16_t score=(endMsg.data[0]<<8)|(endMsg.data[1]);
	uint8_t index=9;
	highscore[9]=score;
	for(uint8_t i = 9; i>0;i--){
		if(highscore[i]>highscore[i-1]){
			//printf("bigger than : %i",i-1);
			score=highscore[i-1];
			highscore[i-1]=highscore[i];
			highscore[i]=score;
			index=i-1;
		}
	}
	gui_drawGameEnd(highscore,index,highscore[index]);
}

void game_sram(void){
	can_message_t receive;
	can_message_t * msg = malloc(sizeof(can_message_t));
	msg->id=50;
	msg->length=1;
	msg->data[0]=0;
	can_messageSend(msg,MCP_TXB1CTRL);
	receive=can_dataReceive();
	while (receive.id!=51){
		receive=can_dataReceive();
	}
	gui_clearAll();
	gui_update();
	gui_drawRectangle(0,0,127,63);
	gui_putString(30,2,"SRAM test");
	gui_putString(2,3,"%4d write errors",receive.data[0]);
	gui_putString(2,4,"%4d read errors",receive.data[1]);
	gui_update();
}

void game_highscore(void){
	gui_clearAll();
	gui_putString(30,0,"HIGHSCORES");
	for (uint8_t i = 0;i<8;i++){
		gui_putString(10,i+1,"%i: %10i",i+1,highscore[i]);
	}
}