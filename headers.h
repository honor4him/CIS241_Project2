#include <stdio.h>
#include <stdlib.h>

#ifndef __HEADERS_
#define __HEADERS_

// Header file containing functions used in thomas.c
// By Zachary Thomas

// Struct to hold data for inventory items
struct list{
	char product[20];
	char unit[20];
	int price;
	int quan;
	struct list *next;

};

// Functions defined in thomas.c along with
// function descriptions.

void displayMenu();
struct list* createList();
void deleteProduct(struct list * head, const char * product);
void clearList();
struct list* searchProduct(struct list * head, const char * search);
void displayAll(struct list * head);
void purchase(struct list * head, char * product);
void sell(struct list * head, char * product);
struct list* createAtTail(struct list * head, struct list *temp);
void toString(struct list * temp);
void saveFile(struct list * head);

#endif
