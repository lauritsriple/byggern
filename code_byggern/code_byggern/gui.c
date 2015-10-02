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

gui_item_t gui_createMenu(char *parent, char ** menuItems){
	gui_item_t * prev=NULL;
	gui_item_t * first=NULL;
	uint8_t i=0;
	while (menuItems[i]!=NULL){ //iterates over menu items
		gui_item_t *item = (gui_item_t *) malloc(sizeof(item)); //creates new item
		//item->parent=parent;
		item->name=menuItems[i];
		printf("%s\n",menuItems[i]);
		item->prev=prev;
		prev=item;
		if (i>0){
			item->prev->next=item;
		}
		else {
			first=item;
		}
		i++;
	}
	first->prev=prev;
	prev->next=first;
	return *first;
}

/*
gui_item_t gui_createMenu(char *parentName, char ** menuItems){
	if (parentName!=NULL){ //submenu
		//find node with parentName
		//parent=gui_searchNode(parentName,'km');
	}
	gui_item_t * prev=NULL;
	gui_item_t * first=NULL;
	uint8_t i=0;
	while (menuItems[i]!=NULL){ //iterates over menu items
		gui_item_t *item = (gui_item_t *) malloc(sizeof(item)); //creates new item
		//item->parent=parent;
		item->name=menuItems[i];
		printf("%s\n",menuItems[i]);
		item->prev=prev;
		prev=item;
		if (i>0){
			item->prev->next=item;
		}
		else {
			first=item;
		}
		i++;
	}
	first->prev=prev;
	prev->next=first;
	return *first;
}*/

