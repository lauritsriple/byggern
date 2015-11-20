/*
 * gui.h
 *
 * Created: 17.11.2015 13:15:35
 *  Author: medlem
 */ 


#ifndef GUI_H_
#define GUI_H_

#include "menu.h"
#include <stdint.h>

void gui_update(void);
void gui_swap(uint8_t* a, uint8_t* b);
void gui_setPixel(uint8_t posx, uint8_t posy, uint8_t val);
void gui_drawLine(uint8_t pos1x, uint8_t pos1y,uint8_t pos2x, uint8_t pos2y);
void gui_clearAll(void);
void gui_drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void gui_drawRectangleFilled(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void gui_drawCircle(uint8_t x, uint8_t y, uint8_t r);
void gui_drawCircleFill(uint8_t centreX, uint8_t centreY, uint8_t rad);
void gui_drawMenu(menu_item_t* menu,uint8_t selected);
void gui_putChar(uint8_t x,uint8_t page, char c);
void gui_invertPage(uint8_t page,uint8_t offset);
void gui_putString(uint8_t x,uint8_t page, char * string, ...);
void gui_drawPinout(char port);
void gui_drawPortF(void);
void gui_drawPortD(void);
void gui_drawPortB(void);
void gui_drawAdcTouch(void);
void gui_drawSomething(void);
void gui_drawMalfunction(void);
void gui_drawBluethooth(void);
void gui_drawGameStart(void);
void gui_drawGame(uint16_t score);
void gui_drawGameEnd(uint16_t * highscore, uint8_t index,uint16_t score);


#endif /* GUI_H_ */