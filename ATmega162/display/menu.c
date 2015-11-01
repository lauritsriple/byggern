/*
 * gui.c
 *
 * Created: 25.09.2015 11:15:06
 *  Author: laurittr
 */ 

#include <stdlib.h>
#include "menu.h"

static menu_item_t* mainMenu;
static uint8_t menu_initialized;

//private: creates a new menuitem (initializer)
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

//private: Assigns the right parent pointers. recursive.
static void menu_fix_parents_recursive(menu_item_t* menu){
	for (uint8_t i=0;i<menu->num_childMenus;i++){
		menu->childMenus[i]->parent=menu;
		menu_fix_parents_recursive(menu->childMenus[i]);
	}
}


//private: creates the whole menu structure
//if full memory, the menu, and submenustrings can be stored in progmem
void menu_create(void){
	mainMenu= menu_new("Main menu",NULL,3);
	mainMenu->childMenus[0]= menu_new("Submenu1",NULL,2);
	mainMenu->childMenus[0]->childMenus[0]= menu_new("subsubmenu11",NULL,0);
	mainMenu->childMenus[0]->childMenus[0]= menu_new("subsubmenu12",NULL,0);
	mainMenu->childMenus[0]= menu_new("Submenu2",NULL,2);
	mainMenu->childMenus[0]->childMenus[0]= menu_new("subsubmenu21",NULL,0);
	mainMenu->childMenus[0]->childMenus[0]= menu_new("subsubmenu22",NULL,0);
	mainMenu->childMenus[0]= menu_new("Submenu3",NULL,0);
	menu_fix_parents_recursive(mainMenu);
}

menu_item_t* menu_get(void){
	if (!menu_initialized){
		menu_create();
		menu_initialized=1;
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
		if (m->parent->childMenus[i]==m){
			return i;
		}
		i++;
	}
	return -1;
}


menu_item_t* menu_up(menu_item_t* const menu){
	if (menu->parent!=NULL){
		return menu->parent;
	}
	return menu;
}

menu_item_t* menu_down(menu_item_t* const menu){
	if (menu->childMenus[0]!=NULL){
		return menu->childMenus[0];
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
		return menu->parent->childMenus[0]; //if next at end of list, go to first elem
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
		return menu->parent->childMenus[menu->parent->num_childMenus-1]; //if prev at start of list, goto last elem
	}
	return menu;
}















