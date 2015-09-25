/*
 * gui.h
 *
 * Created: 25.09.2015 11:15:15
 *  Author: laurittr
 */ 


#ifndef GUI_H_
#define GUI_H_

typedef struct gui_item_t gui_item_t;
struct gui_item_t {
	gui_item_t *parent;
	gui_item_t *child;
	gui_item_t *next;
	gui_item_t *prev;
	char* name;
};

//gui_item_t gui_createMenu(gui_item_t *parent, char **menuItems);
gui_item_t gui_searchNode(gui_item_t topNode, char* nodeName);
gui_item_t gui_createMenu(char* parentName,char **menuItems);
gui_item_t gui_createMenuSystem();
void gui_DrawOled
void gui_Traversere(next,prev,up,down)
void gui_
 
#endif /* GUI_H_ */