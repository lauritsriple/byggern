/*
 * ArudinoMega2560.c
 *
 * Created: 16.10.2015 09:38:54
 *  Author: laurittr
 */ 

#define F_CPU 16000000

#include <avr/io.h>

#include <util/delay.h>
#include "communication/uart.h"
#include "communication/can.h"
#include "communication/mcp2515defines.h"
#include <stdlib.h>

int main(void){
	uart_init();
	can_init(MODE_NORMAL);
	can_message_t* msg = malloc(sizeof(can_message_t));
	
	while(1){		
		_delay_ms(100);
		can_message_t receive = can_dataReceive();
		int16_t posx = receive.data[0]<<8 | receive.data[1];
		int16_t posy = receive.data[2]<<8 | receive.data[3];
		printf("X:%4i Y:%4i\r",posx,posy);
		/*printf("received: ");
		can_print(receive);*/
	}
}