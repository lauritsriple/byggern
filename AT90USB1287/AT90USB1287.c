/*
 * AT90USB1287.c
 *
 * Created: 31.10.2015 15:29:18
 *  Author: medlem
 */ 

//read the values from joystick
//read the values from touch
//pwm the values from joystick on PB or PD
//spi the values over canbus
//uart to rs232 for debug
//oled control from atmega162 over can
//oled control from atmega162 over parallel if extsel


//#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
//#include "../lib/can.h"
//#include "../lib/uart.h"
//#include "touch.h"
#include "uart.h"
#include "spi.h"




int main(void){
	uart_init();
	touch_init(30, 30, 30, 30);
	//TOUCH DOES NOT WORK WITH JTAG CONNECTED!!!!!!!!!!!!!!!!!
	spi_init();
	can_init();
	adc_init();
	
	uint8_t ls, rs, lb, rb;
	//DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	DDRD |= (1 << 0);
	//DDRD |= (1 << 2);

	//can_message_t* msg = malloc(sizeof(can_message_t));
	//uint8_t oled[8]=0;
	
	while(1)
	{
		_delay_ms(50);
		PORTD ^= (1 << 0);
		//spi_transmit(0x01);
		//for (uint16_t i =0; i<2048;i++){
		//	DDRD^=(1<<0);
		//}
		printf("Sending char 0x01\r");
		//uart_putChar('f');
		/*touch_measure(&ls, &rs, &lb, &rb);
		printf("touchymeasure");
		printf("left slider: %4i\r",ls);
		printf("right slider: %4i\r",rs);
		printf("right button: %4i\r",lb);
		printf("left button: %4i\r",rb);*/
		//joy_pos_t pos = joy_getPos();
		//pwm_set(1,ls);
		//pwm_set(2,rs);
		
		
		/*msg->id=15;
		msg->length=8;
		msg->data[0]=pos.x>>8;
		msg->data[1]=pos.x;
		msg->data[2]=pos.y>>8;
		msg->data[3]=pos.y;
		msg->data[4]=ls;
		msg->data[5]=lb;
		msg->data[6]=rs;
		msg->data[7]=rb;
		can_messageSend(msg);
		
		can_message_t receive = can_dataReceive();
		
		
		switch (receive.id){
			case 20: ;
				for (uint8_t i = 0 ;i<8;i++){
					//oled_put(receive->data[i]); or something like this
				}
			default:
				break;
				
		}*/
		

	}
}