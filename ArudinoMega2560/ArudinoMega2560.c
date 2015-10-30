/*
 * ArudinoMega2560.c
 *
 * Created: 16.10.2015 09:38:54
 *  Author: laurittr
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communication/uart.h"
#include "communication/can.h"
#include "communication/mcp2515defines.h"
#include "digital/pwm.h"
#include "analog/adc.h"
#include "game.h"
#include "analog/ir.h"
#include "motor.h"
#include <stdlib.h>
#include <stdint.h>

int main(void){
	uart_init();
	adc_init();
	pwm_init();
	//Set start values for pins and center the servo
	DDRE |= (1<<PE3);
	DDRH |= (1 << PH3);
	DDRB |= (1 << PB7);
	
	//DDRD |= (1 << PD0) | (1<<PD1);
	pwm_setValue(33);
	motor_init();
	//initialize canbus.
	can_init(MODE_NORMAL);
	//game_timerStart();
	while(1){
		can_message_t receive = can_dataReceive();
		
		switch(receive.id){
		case 5: ; // reciving message with adc and buttons
			int16_t posx = receive.data[0]<<8 | receive.data[1];
			int16_t posy = receive.data[2]<<8 | receive.data[3];
			pwm_setServo(posx);
			if (posy<0){
				motor_direction(left);
				motor_speed(abs(posy)*2);
			}
			else{
				motor_direction(right);
				motor_speed(abs(posy)*2);
			}
			printf("X:%4i Y:%4i\r",posx,posy);
			break;
			
		case 2050:
			break;
			
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
		PORTH ^=(1 << PH3);
		_delay_ms(1500);
	}
}