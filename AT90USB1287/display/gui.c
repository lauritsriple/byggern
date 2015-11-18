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
/*
|Item1
|Item2
|Item3
|Item4
IItem5 (inverted)
*/
//the font is 5 pixels high and the pagesize is 8
//
/*
-------0 1 2 3 4 5 6 7 8 ... 127-----
*************************************
******[   127 elem list         ]
      [   with 8 rows           ]
      [   which is called       ]
      [   one page              ]
Page0 [                         ]
      [                         ]
      [                         ]
******[                         ]
*************************************
******[                         ]
      [                         ]
      [                         ]
Page1 [                         ]
      [                         ]
      [                         ]
      [                         ]
******[                         ]
*************************************
....
*************************************
******[                         ]
      [                         ]
      [                         ]
Page7 [                         ]
      [                         ]
      [                         ]
      [                         ]
******[                         ]
*************************************
*/

#include "stdint.h"
#include "oled.h"
#include "uart.h"
#include "menu.h"
#include <math.h>
#include <avr/pgmspace.h>
#include "font.h"
#include <avr/io.h>

uint8_t static changed=1;
uint8_t static shroom[9]={28,98,145,177,145,177,145,98,28};
uint8_t static buffer_draw[SCREEN_PAGES][SCREEN_COLS]; // 8x128 and 8bit vertical values
//uint8_t buffer_screen[128][64];
/*
The mapping of the array is 8*128, but we want the to think of pixels as 64*128. 
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
		changed=0;
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
		//printf("Will print line\n\r");
		float a = (float)(pos2y - pos1y)/(pos2x - pos1x);
/*
		printf("a=%4f \n\r",a);
		printf("1->(%i,%i)\n\r",pos1x,pos1y);
		printf("2->(%i,%i)\n\r",pos2x,pos2y);*/
		if(pos2x < pos1x){
			//printf("swap!\n\r");
			gui_swap(&pos1x,&pos2x);
			//printf("afterswap,a:%i,b:%i\n\r",pos1x,pos2x);
			gui_swap(&pos1y,&pos2y);
		}
/*
		printf("1->(%i,%i)\n\r",pos1x,pos1y);
		printf("2->(%i,%i)\n\r",pos2x,pos2y);*/
		for (uint8_t i = pos1x; i <= pos2x; i ++){
			uint8_t posy = (a*(i - pos1x) + pos1y);
			//printf("(x,y)=(%i,%i)",i,posy);
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

void gui_putString(uint8_t x,uint8_t page, char * string){
	uint8_t i = 0;
	while(i < 254 && string[i]!='\0'){
		uint8_t posx=x+(i*(FONT_WIDTH+1));
		gui_putChar(posx,page,string[i]);
		i++;
	}
}


void gui_drawMenu(menu_item_t * menu,uint8_t selected){
	//gui_drawRectangle(0,0,127,63); //Outer border
	gui_clearAll();
	gui_drawLine(0,7,127,7);
	gui_drawLine(10,8,10,64); //Draws the menuscroll
	gui_putString(32,0,menu->name);
	
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

/*	gui_drawText(10,4*8,menu.name);
	gui_invert(10,4*8,127,3*8-1); //selected elem

	menu_item_t * cur=menu;
	menu_item_t * new=menu;
	for (uint8_t i =0; i < 3;i++){
		new=menu_next(cur);
		if (cur!=new){ //still next elems in menu
			gui_drawText(10,5*8+i*8,new.name);
			cur=new;
		else {
			break;
		}
	}
        
	cur=menu;
	new=menu;
	for (uint8_t i = 0; i <3; i++){
		new=menu_next(cur);
		if (cur!=new){ 
			gui_drawText(10,1*8+i*8,new.name);
			cur=new;
		else {
			break;
		}
	}
}
*/
