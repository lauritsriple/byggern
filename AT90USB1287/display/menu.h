/*
 * menu.h
 *
 * Created: 25.09.2015 11:15:15
 *  Author: laurittr
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>

//Struct has private initializer in menu.c
typedef struct menu_item_t menu_item_t;
struct menu_item_t {
	menu_item_t *parent;
	menu_item_t **childMenus;
	uint8_t num_childMenus;
	//menu_item_t *next; //Not needed but easier selection up and down
	//menu_item_t *prev; //Not needed
	char* name;
	void (*fn)(void);
};

menu_item_t* current_menuitem;

//Returns the root node of the menu tree
menu_item_t* get_menu (void);

//returns depth (number of parents)
uint8_t menu_depth(menu_item_t* const menu);

//returns index of this node in parent's submenu list
uint8_t menu_index(menu_item_t* const menu);

//Will try to traverse, and return itself if function "fails".
menu_item_t* menu_down(menu_item_t* const menu);
menu_item_t* menu_up(menu_item_t* const menu);
menu_item_t* menu_next(menu_item_t* const menu);
menu_item_t* menu_prev(menu_item_t* const menu);



#endif /* MENU_H_ */

