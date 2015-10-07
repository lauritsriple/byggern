/*
 * gui.c
 *
 * Created: 25.09.2015 11:15:06
 *  Author: laurittr
 */ 


#include "oled.h"
#include <avr/io.h>
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

//uint8_t pixels[SCREEN_ROWS][SCREEN_COLS]=0;
static menu_item_t* mainMenu;
static uint8_t menu_initialized;

//PRIVATE: creates a new menuitem (initializer)
static menu_item_t* menu_new(char* name, void(*fn)(void), uint8_t num_childMenus){
	menu_item_t* menu= malloc(sizeof(menu_item_t));
	if (num_childMenus){
		menu->childMenus= malloc(sizeof(menu_item_t*) * num_childMenus);
	}
	menu->num_childMenus	= num_childMenus;
	menu->name		= name;
	menu->fn		= fn;

	return menu;
}

//PRIVATE: Assigns the right parent pointers. recursive.
static void menu_fix_parents_recursive(menu_item_t* menu){
	for (uint8_t i=0;i<menu->num_childMenus;i++){
		menu->childMenu[i]->parent=menu;
		menu_fix_parents_recursice(menu->childMenu[i]);
	}
}


//PRIVATE: creates the whole menustructure
void menu_create(void){
	mainMenu= menu_new("Main menu",NULL,3);
	mainMenu->childMenu[0]= menu_new("Submenu1",NULL,2);
	mainMenu->childMenu[0]->childMenu[0]= menu_new("subsubmenu11",NULL,0);
	mainMenu->childMenu[0]->childMenu[0]= menu_new("subsubmenu12",NULL,0);
	mainMenu->childMenu[0]= menu_new("Submenu2",NULL,2);
	mainMenu->childMenu[0]->childMenu[0]= menu_new("subsubmenu21",NULL,0);
	mainMenu->childMenu[0]->childMenu[0]= menu_new("subsubmenu22",NULL,0);
	mainMenu->childMenu[0]= menu_new("Submenu3",NULL,0);
	menu_fix_parents_recursice(mainMenu);
}

menu_item_t* menu_get(void){
	if (!menu_initialized){
		menu_create();
		menu_initialied=1;
	}
	return mainMenu;
}

uint8_t menu_depth(menu_item_t* const menu){
	menu_item_t* m = menu;
	uint8_t depth = 0;
	while (m->parent != NULL){
		m=m->parent;
		depth++;
	}
	return depth;
}

uint8_t menu_index(menu_item_t* const menu){
	menu_item_t* m = menu;
	uint8_t len=m->parent->num_childMenus;
	uint8_t i=0;
	while (i<len){
		if (m->parent->childMenu[i]=m){
			return i;
		}
		i++;
	}
}


menu_item_t* menu_up(menu_item_t* const menu){
	if (menu->parent!=NULL){
		return menu->parent;
	}
	return menu;
}

menu_item_t* menu_down(menu_item_t* const menu){
	if (menu-childMenu[0]!=NULL){
		return menu->childMenu[0];
	}
	return menu;
}

menu_item_t* menu_next(menu_item_t* const menu){
	if (menu->parent){
		for (uint8_t i = 0;i<menu->parent->num_childMenus-1;i++){
			if (menu->parent->childMenus[i]==menu){
				return menu->parent->childMenus[i+1];
			}
		}
		return menu->parent->childMenu[0]; //if next at end of list, go to first elem
	}
	return menu;
}

menu_item_t* menu_prev(menu_item_t* const menu){
	if (menu->parent){
		for (uint8_t i = i;i< menu->parent->num_childMenus;i++){
			if (menu->parent->childMenus[i]==menu){
				return menu->parent->childMenus[i-1];
			}
		}
		return menu->parent->childMenu[menu->parent->num_childMenus-1]; //if prev at start of list, goto last elem
	}
}















