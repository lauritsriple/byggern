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
	}
}

void gui_update(void){
	oled_home();
	for (uint8_t i =0;i<SCREEN_PAGES;i++){
		for(uint8_t j =0;j<SCREEN_COLS;j++){
			oled_put(buffer_draw[i][j]);
		}
		oled_pos(i+1,0);
	}
}

void gui_clearAll(void){
	for (uint8_t i = 0 ; i<SCREEN_COLS;i++){
		for(uint8_t j = 0 ; j<SCREEN_ROWS;j++){
			gui_setPixel(i,j,0);
		}
	}
	gui_update();
}



void gui_swap(uint8_t* a, uint8_t* b){
	 int* temp = a;
	 a = b;
	 b = temp;
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
			gui_swap(&pos1x, &pos2x);
			gui_swap(&pos1y,&pos2y);
		}
		for (uint8_t i = pos1x; i < pos2x; i ++){
			uint8_t posy = (a*(i - pos1x) + pos1y);
			gui_setPixel(i, posy, 1); 
		}		
	}
}

/*
void gui_drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	gui_drawLine(x1, x2);
	gui_drawLine(y1, y2);
	gui_drawLine(x1, y1);
	gui_drawLine(x2, y2);
}

void gui_drawRectanglefilled(pos_t pos1, pos_t pos2){
	pos_t j = pos1; 
	while(j.y <= pos2y){
		gui_drawLine(pos1,j);
		j.y++;
	}
}

void gui_drawCircle(pos_t centre, uint8_t rad){
	for(uint8_t i = centre.x - rad; i < centre.x; i++){
		for(uint8_t j = centre.y - rad; j < centre.y; j++){
			uint8_t r = sqrt(i*i + j*j);
			if (r == rad){
				gui_setPixel(i, j, 1);
			}
		}
	}
}

void gui_drawCircleFill(pos_t centre, uint8_t rad){
	for (uint8_t i = rad; i < 1; i--){
		gui_drawCircle(centre, i);
	}
}

void gui_drawToScreen(void){
	buffer_screen = buffer_draw;
	

}

void gui_drawMenu(menu_item_t* menu){
	gui_drawRectangle(0,0,128,64); //Outer border
	gui_drawLine(5,0,5,64); //Draws the menuscroll
	
	 * for elem in menu
	 * move cursor to right page and column
	 * oledprintf (check if outside border!)
	 *
	 * place title on page=0
	 * place current menu on mid, page=4 [0 1 2 3 4 5 6 7]
	 * iterate trhough nexts and print from page 5-7
	 * iterate through prevs and print frmo page 3-1
	 *
	 */

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
