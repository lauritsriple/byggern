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

/*gui_item_t gui_createMenu(gui_item_t *parent, char ** menuItems){
	gui_item_t * prev=NULL;
	gui_item_t * first=NULL;
	uint8_t i=0;
	while (menuItems[i]!=NULL){ //iterates over menu items
		gui_item_t *item = (gui_item_t *) malloc(sizeof(item)); //creates new item
		item->parent=parent;
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

gui_item_t gui_searchNode(char* nodeName,gui_item_t node){
	
}

gui_item_t gui_createMenu(char *parentName, char ** menuItems){
	gui_item_t parent=NULL;
	if (parentName!=NULL){ //submenu
		//find node with parentName
		parent=gui_searchNode(parentName,node);
	}
	gui_item_t * prev=NULL;
	gui_item_t * first=NULL;
	uint8_t i=0;
	while (menuItems[i]!=NULL){ //iterates over menu items
		gui_item_t *item = (gui_item_t *) malloc(sizeof(item)); //creates new item
		item->parent=parent;
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

gui_createMenu(NULL,["item1","item2","item3"],top); //topmenu
gui_createMenu("item2",["item4","item5"],top);