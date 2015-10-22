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

uint8_t buffer1[128][64];
uint8_t buffer2[128][64];

typedef struct pos_t pos_t;
struct pos_t {
	uint8_t x;
	uint8_t y;
};

void swap(int* a, int* b){
	 int* temp = a;
	 a = b;
	 b = temp;
}

void gui_drawLine(pos_t pos1, pos_t pos2){
	//3 cases; vertically, horisontaly, skraa?	
	if (x1=x2){ //two cases, draw up or down
		if (y2<y1){ //swap
			gui_swap(x1,x2);
			gui_swap(y1,y2);
		}
		for (uint8_t i = y1 ; i < y2;i++){	
			buffer1[x1][i]=1;
		}

	else if (y1=y2) { // draw left or right
		if (x2<x1){ //swap
			uint8_t tmp=x1;
			x1=x2;
			x2;tmp;
		for (uint8_t i=x1;i<x2;i++){
			buffer[i][y1]=1;
		}
	else{ //not straight line, 4 cases
		if (x2<x1) //swap elems


}

void gui_drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void gui_drawRectanglefilled(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void gui_drawCircle(uint8_t centre, uint8_t rad);

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

