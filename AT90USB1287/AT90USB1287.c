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

#include "uart.h"
#include "pwm.h"
#include "board.h"
#include "adc.h"
#include "joy.h"
#include "display/oled.h"
#include "display/menu.h"
#include "display/gui.h"
#include "touch.h"
#include <stdlib.h>

int main(void){
	uint8_t touchMode=1;
	
	board_init();
	uart_init();
	oled_init();
	//can_init(MODE_NORMAL);
	
	/*Since the touch libary wont play nicely with the adc, choose slider or adc on 
	reboot. No button -> touch. There might also be some problems with the adc and the jtag*/
	if (!(SW_PIN & (1<<SW))){
		adc_init();
		joy_init();
		touchMode=0;
	}
	else{
		touch_init(30, 30, 30, 30);
		pwm_init();
	}
	
	uint8_t selected=1;
	menu_item_t *menu=menu_get();
	uint8_t ls, rs, lb, rb;
	//can_message_t* msg13 = malloc(sizeof(can_message_t));
	//can_message_t* msg77 = malloc(sizeof(can_message_t));
	//can_message_t receive;
	gui_drawMenu(menu,selected);
	while(1){
		if (touchMode){
			touch_measure(&ls, &rs, &lb, &rb);
			//printf("ls:%4i,rs:%4i,lb:%4i,rb:%4i\n",ls,rs,lb,rb);
			pwm_set(1,255-ls);
			pwm_set(2,rs);
			//MAP 0-255 to 1- num child menus
			uint8_t mapValue=255/(menu->num_childMenus+1);
			ls=255-ls;
			uint8_t touchSelected=(ls/mapValue);
		
			if (touchSelected!=selected && touchSelected>=1 && touchSelected<menu->num_childMenus+1){
				selected=touchSelected;
				gui_drawMenu(menu,selected);
			}
			//printf("\n\rRANDOM\n\r");
			if (rb){
				if((selected<=menu->childMenus[selected-1]->num_childMenus) && (menu->childMenus[selected-1]->num_childMenus>0)){
					menu=menu->childMenus[selected-1];
					selected=1;
					gui_drawMenu(menu,selected);
				}
				else if (menu->childMenus[selected-1]->fn != NULL){
					printf("function");
					menu->childMenus[selected-1]->fn();
				}
				//Touch is buggy. Needs to read a couple of time to accept changes.
				//This will prevent functions running many times!
				gui_update();
				_delay_ms(400);
				for(uint8_t i =0;i<16;i++){
					touch_measure(&ls, &rs, &lb, &rb);
					_delay_ms(10);
				}
			}
			else if(lb){
				if (menu->parent!=NULL){
					menu=menu->parent;
					selected=1;
					gui_drawMenu(menu,selected);
				}
			}
		}
		else{ //We are in adc-mode
			joy_pos_t pos=joy_getPos();
			printf("X:%4i Y:%4i\r",pos.x,pos.y);
			if (pos.y>90 && selected > 1){
				selected--;
				gui_drawMenu(menu,selected);
			}
			else if (pos.y<-90 && selected < menu->num_childMenus){
				selected++;
				gui_drawMenu(menu,selected);
			}
			if (!(JOY_PIN & (1<<JOY))){
				if((selected<=menu->childMenus[selected-1]->num_childMenus) && (menu->childMenus[selected-1]->num_childMenus>0)){
					menu=menu->childMenus[selected-1];
					selected=1;
					gui_drawMenu(menu,selected);
				}
				else if (menu->childMenus[selected-1]->fn != NULL){
					printf("function");
					menu->childMenus[selected-1]->fn();
				}
				gui_update();
				_delay_ms(400);
			}
			else if(!(SW_PIN & (1<<SW))){
				if (menu->parent!=NULL){
					menu=menu->parent;
					selected=1;
					gui_drawMenu(menu,selected);
				}
			}
			
		}
/*
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
		can_messageSend(msg13,MCP_TXB1CTRL);* /
		
		/ *if (!(SPI_PIN & SPI_CS_MCP2515)){
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
		
		gui_update();
		LED_PORT ^= (1 << LED1);
	}
}