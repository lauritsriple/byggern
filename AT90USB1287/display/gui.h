/*
 * gui.h
 *
 * Created: 17.11.2015 13:15:35
 *  Author: medlem
 */ 


#ifndef GUI_H_
#define GUI_H_

void gui_update(void);
void gui_swap(int* a, int *b);
void gui_setPixel(uint8_t posx, uint8_t posy, uint8_t val);
void gui_drawLine(uint8_t pos1x, uint8_t pos1y,uint8_t pos2x, uint8_t pos2y);
void gui_clearAll(void);


#endif /* GUI_H_ */