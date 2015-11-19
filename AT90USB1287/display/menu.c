/*
 * gui.c
 *
 * Created: 25.09.2015 11:15:06
 *  Author: laurittr
 */ 
#include <stdlib.h>
#include "menu.h"

//Needed for function calls:
#include "../board.h"	//blink
#include <util/delay.h>	//blink
#include "gui.h" //gui.h


static menu_item_t* mainMenu;
static uint8_t menu_initialized;

void blink(void){
	for (uint8_t i = 0;i<8;i++){
		LED_PORT ^=(1<<LED1);
		//printf("BLINK: %i",i);
		_delay_ms(100);
	}
}

//private: creates a new menuitem (initializer)
static menu_item_t* menu_new(char* a_name, void(*a_fn)(void), uint8_t a_num_childMenus){
	menu_item_t* menu= malloc(sizeof(menu_item_t));
	if (a_num_childMenus){
		menu->childMenus= malloc(sizeof(menu_item_t*) * a_num_childMenus);
	}
	menu->num_childMenus=a_num_childMenus;
	menu->name			=a_name;
	menu->fn			=a_fn;

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
void static menu_create(void){
	mainMenu= menu_new("Soleonid Balls!",NULL,7);
	mainMenu->childMenus[0]= menu_new("Ping Pong",NULL,2);
	mainMenu->childMenus[0]->childMenus[0]= menu_new("Play the game",NULL,0);
	mainMenu->childMenus[0]->childMenus[1]= menu_new("See highscores",NULL,0);
	mainMenu->childMenus[1]= menu_new("Settings",NULL,2);
	mainMenu->childMenus[1]->childMenus[0]= menu_new("subsubmenu21",NULL,0);
	mainMenu->childMenus[1]->childMenus[1]= menu_new("subsubmenu22",NULL,0);
	mainMenu->childMenus[2]= menu_new("Pinout",NULL,3);
	mainMenu->childMenus[2]->childMenus[0]= menu_new("Port B",gui_drawPortB,0);
	mainMenu->childMenus[2]->childMenus[1]= menu_new("Port D",gui_drawPortD,0);
	mainMenu->childMenus[2]->childMenus[2]= menu_new("Port F",gui_drawPortF,0);
	mainMenu->childMenus[3]= menu_new("Blink the led",blink,0);
	mainMenu->childMenus[4]= menu_new("Adc/Touch info",gui_drawAdcTouch,0);
	mainMenu->childMenus[5]= menu_new("Draw random stuff",gui_drawSomething,0);
	mainMenu->childMenus[6]= menu_new("Malfunction board",NULL,0);
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















