// This is a test gui. in Beta
//

//we need one function to draw and redraw the menu. Should be fairly simple
//draw line
//draw rectangle
//draw circle
//
//some move functions. (matrix transformations)
//
//Double buffer approach:
//All the draw functions writes to a double array. This is buffer1.
//When we want it one the screen copy buffer1 to buffer2 and draw buffer2 on screen.
//Buffer 1 = buffer 2, and changes can be made to buffer 1 without affecting the display.
//This ensures unfinished drawings to be animated
//
#include "stdint.h"
#include "oled.h"
#include "uart.h"
#include "menu.h"
#include <math.h>
#include <avr/pgmspace.h>
#include "font.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

uint8_t static changed=1;  //Whether array has changed and not been printed on screen.
uint8_t static shroom[9]={28,98,145,177,145,177,145,98,28}; //This is the selector shroom!
uint8_t static buffer_draw[SCREEN_PAGES][SCREEN_COLS]; // 8x128 and 8bit vertical values

/*
The mapping of the array is words in 8*128, but we want the to think of pixels as 64*128. 
We will map it in the setPixel function
*/

void gui_setPixel(uint8_t posx, uint8_t posy, uint8_t val){
	if ((posx < SCREEN_COLS && posx >= 0) && (posy < SCREEN_ROWS && posy >= 0)){
		//pos, within range. Map to right array. posx is correct
		//posy/8 -> 30/8=3 rest = 6
		if (val==1){ //ON
			buffer_draw[posy/SCREEN_PAGES][posx]=buffer_draw[posy/SCREEN_PAGES][posx] | (1 << posy%SCREEN_PAGES);
		}
		else if (val==0){ //OFF
			buffer_draw[posy/SCREEN_PAGES][posx]=buffer_draw[posy/SCREEN_PAGES][posx] & ~(1 << posy%SCREEN_PAGES);
		}
		else if (val=3){ //INVERT
			buffer_draw[posy/SCREEN_PAGES][posx]=buffer_draw[posy/SCREEN_PAGES][posx] ^(1 << posy%SCREEN_PAGES);
		}
		changed=1;
	}
	
}


void gui_update(void){
	if (changed){
		oled_home();
		for (uint8_t i =0;i<SCREEN_PAGES;i++){
			for(uint8_t j =0;j<SCREEN_COLS;j++){
				oled_put(buffer_draw[i][j]);
			}
			oled_pos(i+1,0);
		}
		changed=1;
	}
}

void gui_clearAll(void){
	for (uint8_t i = 0 ; i<SCREEN_COLS;i++){
		for(uint8_t j = 0 ; j<SCREEN_ROWS;j++){
			gui_setPixel(i,j,0);
		}
	}
}

void gui_swap(uint8_t* a, uint8_t* b){
	 uint8_t temp = *a;
	 *a = *b;
	 *b = temp;
}

void gui_drawLine(uint8_t pos1x, uint8_t pos1y,uint8_t pos2x, uint8_t pos2y){					//3 cases; vertically, horisontaly, skraa?	
	if (pos1x == pos2x){									//vertical, draw up or down
		if (pos2y < pos1y){								//swap
			gui_swap(&pos1y, &pos2y);
			
		}
		for (uint8_t i = pos1y; i < pos2y;i++){
			gui_setPixel(pos1x, i, 1);	
		}
	}
	else if (pos1y == pos2y){								//horisontal draw left or right
		if (pos2x < pos1x){								//swap
			gui_swap(&pos1x, &pos2x);
		}
		for (uint8_t i = pos1x; i < pos2x; i++){
			gui_setPixel(i, pos1y, 1);
		}
	}
	else{													//skraa, 4 case
		float a = (float)(pos2y - pos1y)/(pos2x - pos1x);
		if(pos2x < pos1x){
			gui_swap(&pos1x,&pos2x);
			gui_swap(&pos1y,&pos2y);
		}
		for (uint8_t i = pos1x; i <= pos2x; i ++){
			uint8_t posy = (a*(i - pos1x) + pos1y);
			gui_setPixel(i, posy, 1); 
		}		
	}
}


void gui_drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	gui_drawLine(x1,y1,x1,y2);
	gui_drawLine(x1,y1,x2,y1);
	gui_drawLine(x2,y2,x2,y1);
	gui_drawLine(x2, y2,x1,y2);
}

void gui_drawRectangleFilled(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	for(uint8_t i = x1; i <= x2; i++){
		gui_drawLine(i,y1,i,y2);
	}
}


void gui_drawCircle(uint8_t centreX, uint8_t centreY, uint8_t r){
	for(int i =-r; i <= r; i++){
		uint16_t posy=sqrt((uint16_t)r*r-((uint16_t)i*i));
		gui_setPixel(i+centreX,posy+centreY,1);
		gui_setPixel(i+centreX,-posy+centreY,1);
	}
		for(int i =-r; i <= r; i++){
			uint32_t rad=r*r;
			int j=i;
			uint16_t sqr=sqrt(rad-j);
			uint16_t posy=sqrt((uint16_t)r*r-((uint16_t)i*i));
			gui_setPixel(posy+centreX,i+centreY,1);
			gui_setPixel(-posy+centreX,i+centreY,1);
		}
}


void gui_drawCircleFill(uint8_t centreX, uint8_t centreY, uint8_t rad){
	for (uint8_t i = rad; i > 0; i--){
		gui_drawCircle(centreX,centreY, i);
	}
}

void gui_invertPage(uint8_t page,uint8_t offset){
	for (uint8_t i=offset;i<128;i++){
		for (uint8_t j= 0;j<8;j++){
			gui_setPixel(i,j+(page*8),2);
		}
	}
}

void gui_drawSelector(uint8_t page){
	for(uint8_t i=0;i<9;i++){
		for(uint8_t j=0;j<8;j++){
			if (shroom[i] & (1<<j)){
				gui_setPixel(i,j+(page*8),1);
			}
		}
	}
}

void gui_putChar(uint8_t x,uint8_t page, char c){
	for(uint8_t i=x;i<x+FONT_WIDTH;i++){
		uint8_t tmp=pgm_read_byte(&font[c-FONT_OFFSET][i-x]);
		for(uint8_t j=0;j<8;j++){
			if (tmp & (1<<j)){
				gui_setPixel(i,j+(page*8),1);
			}
		}
	}
}

void gui_putString(uint8_t x,uint8_t page, char * string, ...){
	char buffer[64];
	va_list v;
	va_start(v,string);
	vsprintf(buffer, string, v);
	va_end(v);
	
	uint8_t i = 0;
	while(i < 64 && buffer[i]!='\0'){
		uint8_t posx=x+(i*(FONT_WIDTH+1));
		gui_putChar(posx,page,buffer[i]);
		i++;
	}
}


void gui_drawMenu(menu_item_t * menu,uint8_t selected){
	gui_clearAll();
	gui_drawLine(0,7,127,7);
	gui_drawLine(10,8,10,64); //Draws the menuscroll
	gui_putString(16,0,menu->name);
	
	if ((menu->num_childMenus)>7){
		//WRAP IT NICELY, too many submenus to fit properly 
	}
	else{
		for (uint8_t i=0;i<(menu->num_childMenus);i++){
			gui_putString(13,i+1,(menu->childMenus[i]->name));
		}
		gui_drawSelector(selected);
		//inverting many times to make it look right. Could have been done
		//otherwise, but didn't want to make more functions
		gui_invertPage(selected,0);
		gui_invertPage(selected,10);
		gui_invertPage(selected,11);
	}
}

void gui_drawPortB(void){
	gui_drawPinout('b');
}

void gui_drawPortD(void){
	gui_drawPinout('d');
}

void gui_drawPortF(void){
	gui_drawPinout('f');
}

void gui_drawPinout(char port){
	gui_clearAll();
	gui_drawRectangle(0,0,127,63);
	gui_drawLine(0,32,127,32);
	for (uint8_t i = 0;i<4;i++){
		gui_drawLine(i*32,0,i*32,63);
	}
	if (port=='b'){
		gui_putString(4,1,"PB1");
		gui_putString(4,2,"SPI");
		gui_putString(4,3,"SCK");
		
		gui_putString(36,1,"PB3");
		gui_putString(36,2,"SPI");
		gui_putString(36,3,"MISO");
		
		gui_putString(68,1,"PB5");
		gui_putString(68,2,"LED1");
		
		gui_putString(100,1,"PB7");
		gui_putString(100,2,"PWM1");
		
		gui_putString(4,5,"PB0");
		gui_putString(4,6,"SPI");
		gui_putString(4,7,"CS");
		
		gui_putString(36,5,"PB2");
		gui_putString(36,6,"SPI");
		gui_putString(36,7,"MOSI");
		
		gui_putString(68,5,"PB4");
		gui_putString(68,6,"JOY");
		gui_putString(68,7,"BTN");
		
		gui_putString(100,5,"PB6");
		gui_putString(100,6,"PWM2");
	}
	else if (port=='d'){
		gui_putString(4,1,"PD1");
		gui_putString(4,2,"CAN");
		gui_putString(4,3,"INT");
		
		gui_putString(36,1,"PD3");
		gui_putString(36,2,"UART");
		gui_putString(36,3,"TX");
		
		gui_putString(68,1,"PD5");
		gui_putString(68,2,"NC");
		
		gui_putString(100,1,"PD7");
		gui_putString(100,2,"NC");
		
		gui_putString(4,5,"PD0");
		gui_putString(4,6,"NC");
		
		gui_putString(36,5,"PD2");
		gui_putString(36,6,"UART");
		gui_putString(36,7,"RX");
		
		gui_putString(68,5,"PD4");
		gui_putString(68,6,"SW");
		gui_putString(68,7,"!TCH");
		
		gui_putString(100,5,"PD6");
		gui_putString(100,6,"NC");
		
	}
	else if (port=='f'){
		gui_putString(4,1,"PF0");
		gui_putString(4,2,"ADC");
		gui_putString(4,3,"CH0");
		
		gui_putString(36,1,"PF1");
		gui_putString(36,2,"ADC");
		gui_putString(36,3,"CH1");
		
		gui_putString(68,1,"PF2");
		gui_putString(68,2,"ADC");
		gui_putString(68,3,"CH2");
		
		gui_putString(100,1,"PF3");
		gui_putString(100,2,"ADC");
		gui_putString(100,3,"CH3");
	}
}

void gui_drawAdcTouch(void){
	//info about stupid malfunction board
	gui_clearAll();
	gui_drawRectangle(0,0,127,63);
	gui_putString(4,1,"Use Joystick?");
	gui_putString(4,2,"Hold down SW1 ");
	gui_putString(4,3,"during reset.");
	gui_putString(4,4,"ADC and");
	gui_putString(4,5,"Qtouch don't");
	gui_putString(4,6,"like each other.");
}

void gui_drawSomething(void){
	gui_clearAll();
	for (uint8_t i = 0;i<4;i++){
		gui_drawCircle(10+i*20,50-i*10,5+i*10);
		gui_update();
		_delay_ms(1000);
	}
	gui_clearAll();
	gui_drawLine(10,10,80,60);
	gui_update();
	_delay_ms(1000);
	gui_drawLine(50,50,120,10);
	gui_update();
	_delay_ms(1000);
	gui_drawRectangle(30,10,100,60);
	gui_update();
	_delay_ms(1000);
	gui_drawRectangleFilled(100,40,127,63);
	gui_update();
	_delay_ms(1000);
	gui_drawCircleFill(110,15,10);
	gui_update();
	_delay_ms(1000);
	gui_clearAll();
	gui_putString(10,4,"That's it!");
	gui_putString(10,5,"go up or down");
	gui_update();
}


void gui_drawMalfunction(void){
	uint8_t ls,rs,lb,rb;
	touch_measure(&ls,&rs,&lb,&rb);
	while(lb!=1){
		touch_measure(&ls,&rs,&lb,&rb);
		gui_clearAll();
		gui_putString(10,0,"Malfunction board");
		gui_putString(10,1,"ls: ");
		gui_putString(30,1,"%d",255-ls);
		gui_putString(10,2,"rs: ");
		gui_putString(30,2,"%d",rs);
		gui_putString(10,3,"lb: ");
		gui_putString(30,3,"%d",lb);
		gui_putString(10,4,"rb: ");
		gui_putString(30,4,"%d",rb);
		gui_drawLine((255-ls)>>1,63,(255-ls)>>1,55);
		gui_drawLine(rs>>1,54,rs>>1,46);
		gui_update();
	}
}
