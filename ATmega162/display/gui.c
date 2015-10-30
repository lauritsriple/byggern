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

uint8_t buffer_draw[128][64];
uint8_t buffer_screen[128][64];

typedef struct pos_t pos_t;
struct pos_t {
	uint8_t x;
	uint8_t y;
};

void gui_swap(int* a, int* b){
	 int* temp = a;
	 a = b;
	 b = temp;
}

void gui_setPixel(uint8_t posx, uint8_t posy, uint8_t val){
	if (posx < 128 && posx > 0 && posy < 64 && posy > 0){
		buffer_draw[posx][posy];
	}
}

void gui_drawLine(pos_t pos1, pos_t pos2){					//3 cases; vertically, horisontaly, skraa?	
	if (pos1.x == pos2.x){									//vertical, draw up or down
		if (pos2.y < pos1.y){								//swap
			gui_swap(pos1.y, pos2.y);
		}
		for (uint8_t i = pos1.y; i < pos2.y;i++){
			gui_setPixel(pos1.x, i, 1);	
		}
	}
	else if (pos1.y == pos2.y){								//horisontal draw left or right
		if (pos2.x < pos1.x){								//swap
			gui_swap(pos1.x, pos2.x);
		}
		for (uint8_t i = pos1.x; i < pos2.x; i++){
			gui_setPixel(i, pos1.y, 1);
		}
	}
	else{													//skraa, 4 case
		float_t a = (pos2.y - pos1.y)/(pos2.x - pos1.x);
		if( pos2.x < pos1.x){
			gui_swap(pos1.x, pos2.x);
			gui_swap(pos1.y, pos2.x);
		}
		for (uint8_t i = pos1.x; i < pos2 x; i ++){
			uint8_t posy = a*(i - pos1.x) + pos1.y;
			gui_setPixel(i, posy, 1); 
		}		
	}
}

void gui_drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	gui_drawLine(x1, x2);
	gui_drawLine(y1, y2);
	gui_drawLine(x1, y1);
	gui_drawLine(x2, y2);
}

void gui_drawRectanglefilled(pos_t pos1, pos_t pos2){
	pos_t j = pos1; 
	while(j.y <= pos2.y){
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
	/*
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

	gui_drawText(10,4*8,menu.name);
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
