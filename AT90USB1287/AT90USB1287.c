/*
 * AT90USB1287.c
 *
 * Created: 31.10.2015 15:29:18
 *  Author: medlem
 */ 

//#define F_CPU 16000000 //defined in toolchain

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"
#include "mcp2515defines.h"
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

uint8_t touchMode=1;

int main(void){
	uint8_t bluethooth=0;
	
	board_init();
	uart_init();
	oled_init();
	can_init(MODE_NORMAL);
	
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
		touchMode=1;
	}
	uint8_t selected=1;
	char blue_recv='i';
	menu_item_t *menu=menu_get();
	uint8_t ls, rs, lb, rb;
	gui_drawMenu(menu,selected);
	while(1){
		if(!(SW_PIN & (1<<SW2))){
			while(!(SW_PIN & (1<<SW2))); //take away all rebouncing
			_delay_ms(1000);
			if (bluethooth==0){
				bluethooth=1;
			}
		}
		
		if ((touchMode==1) && (bluethooth==0)){
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
			if (rb){
				if((selected<=menu->childMenus[selected-1]->num_childMenus) && (menu->childMenus[selected-1]->num_childMenus>0)){
					menu=menu->childMenus[selected-1];
					selected=1;
					gui_drawMenu(menu,selected);
				}
				else if (menu->childMenus[selected-1]->fn != NULL){
					menu->childMenus[selected-1]->fn();
				}
				//Touch is buggy. Needs to read a couple of time to accept changes.
				//Also added some delay.
				//This will prevent functions from running many times!
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
		else if ((touchMode==0) && (bluethooth==0)){ //We are in adc-mode
			joy_pos_t pos=joy_getPos();
			//printf("X:%4i Y:%4i\r",pos.x,pos.y);
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
		if (bluethooth){
			blue_recv=uart_getChar();
			if (blue_recv=='u' && selected >1){ //up
				selected--;
				gui_drawMenu(menu,selected);
			}
			else if (blue_recv=='d' && selected < menu->num_childMenus){ //down
				selected++;
				gui_drawMenu(menu,selected);
			}
			else if (blue_recv=='p'){ //press
				if((selected<=menu->childMenus[selected-1]->num_childMenus) && (menu->childMenus[selected-1]->num_childMenus>0)){
					menu=menu->childMenus[selected-1];
					selected=1;
					gui_drawMenu(menu,selected);
				}
				else if (menu->childMenus[selected-1]->fn != NULL){
					menu->childMenus[selected-1]->fn();
				}
				gui_update();
			}
			else if(blue_recv=='b'){ //back
				if (menu->parent!=NULL){
					menu=menu->parent;
					selected=1;
					gui_drawMenu(menu,selected);
				}
			}
			else if (blue_recv=='x'){
				bluethooth=0;
			}
		}
		gui_update();
		LED_PORT ^= (1 << LED1);
	}
}