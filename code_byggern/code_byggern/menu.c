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
