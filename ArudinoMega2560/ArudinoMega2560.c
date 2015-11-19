/*
 * ArudinoMega2560.c
 *
 * Created: 16.10.2015 09:38:54
 *  Author: laurittr
 */ 

//#define F_CPU 16000000 //defined in toolchain

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include "boardhack.h"
#include "../lib/uart.h"
#include "../lib/can.h"
#include "../lib/mcp2515defines.h"
#include "drivers/adc.h"
#include "../lib/joy.h"
#include "drivers/pwm.h"
#include "drivers/motor.h"
#include "drivers/ir.h"
#include "game.h"
#include "drivers/pi.h"

uint16_t encoder_startUp(void){
	motor_direction(left);
	motor_speed(85);
	_delay_ms(2500);
	motor_speed(0);
	_delay_ms(500);
	motor_direction(right);
	motor_encoderCounterReset();
	motor_speed(85);
	_delay_ms(2500);
	motor_speed(0);
	_delay_ms(500);
	return motor_encoderRead();
}


int main(void){
	board_init_hack();
	uart_init();
	adc_init();
	pwm_init();
	motor_init();
	can_init(MODE_NORMAL);
	uint8_t game_running=0;
	joy_pos_t pos;
	can_message_t* msg = malloc(sizeof(can_message_t));
	can_message_t receive;
	uint16_t encoderMax=encoder_startUp();
	uint16_t encoderMap=encoderMax/256;
	pi_controller_t* c = pi_init(10,2);
	while(1){
		receive = can_dataReceive();
		switch(receive.id){
			case 120: ; // reciving message with adc and buttons
				pos.x = receive.data[0]<<8 | receive.data[1];
				pos.y = receive.data[2]<<8 | receive.data[3];
				pwm_setServo(pos.x);
				if (pos.y<0){
					motor_direction(left);
					motor_speed(abs(pos.y)*2);
				}
				else{
					motor_direction(right);
					motor_speed(abs(pos.y)*2);
				}
				if (receive.data[4]){
					game_solenoid();
				}
				//printf("X:%4i Y:%4i\r",pos.x,pos.y);
				break;
			
			case 140:
				pwm_setServoSlider(receive.data[1]); //use rs for servo control
				float position = (float)receive.data[0]*encoderMap;
				pi_update(c,position); //ls -> pid controller
				if (receive.data[2]){ //lb -> solenoid
					game_solenoid();
				}
				break;
			
			case 100:
				game_running=1;
				game_timerStart();
				break;
			
			case 2050:
				printf("invalid message or no message\n");
				break;
			
			default:
				break;
		}
		
		if(ir_signal()&&game_running){
			game_timerStop();
			game_running=0;
			uint8_t score=game_getScore();
			msg->id=7;
			msg->length=2;
			//transfer uint16_t to two uint8_t
			msg->data[0]=(score>>8)& 0xff;
			msg->data[0]=score & 0xff;
			can_messageSend(msg,MCP_TXB1CTRL);
		}
		
		if (game_running==0){
			pwm_setServo(0);
			motor_speed(0);
		}
		LED_PORT ^=(1 << LED1);
		pi_calculate(c,motor_encoderRead());
	}
}