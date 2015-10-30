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
#include <stdint.h>

#include "communication/TWI_Master.h"

#define TWI_GEN_CALL         0x00  // The General Call address is 0

// Sample TWI transmission commands
#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

// Sample TWI transmission states, used in the main application.
#define SEND_DATA             0x01
#define REQUEST_DATA          0x02
#define READ_DATA_FROM_BUFFER 0x03

unsigned char TWI_Act_On_Failure_In_Last_Transmission ( unsigned char TWIerrorMsg )
{
	// A failure has occurred, use TWIerrorMsg to determine the nature of the failure
	// and take appropriate actions.
	// Se header file for a list of possible failures messages.
	
	// Here is a simple sample, where if received a NACK on the slave address,
	// then a retransmission will be initiated.
	
	if ( (TWIerrorMsg == TWI_MTX_ADR_NACK) | (TWIerrorMsg == TWI_MRX_ADR_NACK) )
	TWI_Start_Transceiver();
	
	return TWIerrorMsg;
}

int main(void){
	uart_init();
	adc_init();
	pwm_init();
	//Set start values for pins and center the servo
	DDRE |= (1<<PE3);
	DDRB |= (1 << PB7);
	//DDRD |= (1 << PD0) | (1<<PD1);
	pwm_setValue(33);
	
	//initialize canbus.
	can_init(MODE_NORMAL);
	printf("here");
	can_message_t* msg = malloc(sizeof(can_message_t));
	
	// TWI initializtion, also creating buffer
	
	TWI_Master_Initialise();
	sei();

	
	//game_timerStart();
	uint8_t it;
	while(1){
		/*unsigned char messageBuf[3] = {
			0b01011100,
			0,
			it++
		};
		TWI_Start_Transceiver_With_Data( messageBuf, 3 );*/
		
		//_delay_ms(10);
		can_message_t receive = can_dataReceive();
		//can_print(receive);
		
		switch(receive.id){
		case 5: ;
			int16_t posx = receive.data[0]<<8 | receive.data[1];
			int16_t posy = receive.data[2]<<8 | receive.data[3];
			pwm_setServo(posx);
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
		//printf("X:%4i Y:%4i\r",posx,posy);

		//printf("received: ");
		//uint16_t value = adc_read(0);
		//printf("adc value: %4i \n", value);
		it++;
		if (it==100){
			PORTB ^= (1<<PB7);
		}
		
	}
}