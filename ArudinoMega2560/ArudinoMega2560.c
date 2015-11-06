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
#include "../lib/adc.h"
#include "../lib/joy.h"
#include "drivers/pwm.h"
#include "drivers/motor.h"
#include "drivers/ir.h"
#include "game.h"



int main(void){
	//Set start values for pins and center the servo
	//DDRE |= (1<<PE3); //PWM
	//DDRH |= (1 << PH3); //LED
	//DDRB |= (1 << PB7); what is on PB7?
	//DDRD |= (1 << PD0) | (1<<PD1);
	board_init_hack();
	uart_init();
	adc_init();
	pwm_init();
	motor_init();
	can_init(MODE_NORMAL);
	
	joy_pos_t pos;
	
	//game_timerStart();
	while(1){
		can_message_t receive = can_dataReceive();
		
		switch(receive.id){
		case 5: ; // reciving message with adc and buttons
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
			printf("X:%4i Y:%4i\r",pos.x,pos.y);
			break;
			
		case 13: ;
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
			break;
			printf("X:%4i Y:%4i\r",pos.x,pos.y);
			
		default:
			break;
		}
		/*if(ir_signal()){
			game_timerStop();
		}
		*/
		//printf("score is: %4i\n",game_getScore());
		

		//printf("received: ");
		//uint16_t value = adc_read(0);
		//printf("adc value: %4i \n", value);
		LED_PORT ^=(1 << LED1);
		//_delay_ms(1500);
	}
}