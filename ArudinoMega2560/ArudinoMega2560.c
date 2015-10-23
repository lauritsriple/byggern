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
#include <stdlib.h>

int main(void){
	uart_init();
	adc_init();
	can_init(MODE_NORMAL);
	can_message_t* msg = malloc(sizeof(can_message_t));
	DDRE |= (1<<PE3);
	pwm_init();
	pwm_setValue(33);
	DDRB |= (1 << PB7);
	sei();
	
	while(1){		
		//_delay_ms(100);
		can_message_t receive = can_dataReceive();
		int16_t posx = receive.data[0]<<8 | receive.data[1];
		int16_t posy = receive.data[2]<<8 | receive.data[3];
		game_timerStart();
		while(!ir_signal());
		game_timerStop();
		printf("score is: %4i\n",game_getScore());
		printf("X:%4i Y:%4i\r",posx,posy);
		pwm_setServo(posx);
		printf("received: ");
		can_print(receive);
		uint16_t value = adc_read(0);
		printf("adc value: %4i \n", value);
		PORTB ^= (1<<PB7);
	}
}