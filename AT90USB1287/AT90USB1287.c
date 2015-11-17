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


//#define F_CPU 16000000 //defined in toolchain

#include <avr/io.h>
#include <util/delay.h>
//#include "can.h"
//#include "mcp2515defines.h"
//#include "touch.h"
//#include "uart.h"
//#include "pwm.h"
#include "board.h"
//#include "adc.h"
//#include "joy.h"
#include "display/oled.h"

int main(void){
	board_init();
	oled_init();
	//uart_init();
	//touch_init(30, 30, 30, 30); //TOUCH DOES NOT WORK WITH JTAG CONNECTED!!!!!!!!!!!!!!!!!
	//adc_init();
	//pwm_init();
	//joy_init();
	//can_init(MODE_NORMAL);
	
	//uint8_t ls, rs, lb, rb;

	//can_message_t* msg13 = malloc(sizeof(can_message_t));
	//can_message_t* msg77 = malloc(sizeof(can_message_t));
	//can_message_t receive;
	//joy_pos_t pos = joy_getPos();
	//printf("Initialization complete");
	//_delay_ms(100);
	//_delay_ms(100);
	//oled_home();
	//oled_clear_all();
	oled_clear_all();
	while(1){
		for (uint8_t i = 0; i<8;i++){
			oled_fill_page(i);
			_delay_ms(10);
		}
		oled_clear_all();
		oled_home();
		for(uint8_t j=0;j<4;j++){
			oled_pos(j,0);
			for (uint8_t i =0;i<8;i++){
				oled_put_char('c');
				_delay_ms(10);
			}
		}
		
		//printf("tried to print c to oled\n\r");
/*
		touch_measure(&ls, &rs, &lb, &rb);
		pwm_set(1,255-ls);
		pwm_set(2,rs);
		pos=joy_getPos();
		
		msg13->id=13;
		msg13->length=4;
		msg13->data[0]=pos.x>>8;
		msg13->data[1]=pos.x;
		msg13->data[2]=pos.y>>8;
		msg13->data[3]=pos.y;
		
		msg77->id=77;
		msg77->length=4;
		msg77->data[0]=255-ls;
		msg77->data[1]=rs;
		msg77->data[2]=lb;
		msg77->data[3]=rb;
		
		printf("sending:  ");
		can_print(*msg13);
		can_messageSend(msg13,MCP_TXB1CTRL);*/
		
		LED_PORT ^= (1 << LED1);
		_delay_ms(100);
		
		/*if (!(SPI_PIN & SPI_CS_MCP2515)){
			can_message_t receive = can_dataReceive();
			switch (receive.id){
				case 20: ;
					for (uint8_t i = 0 ;i<8;i++){
						//oled_put(receive->data[i]); or something like this
					}
				case 46:
					//message that contains confidential information
					break;
				default:
					break;	
			}
		}*/
	}
}