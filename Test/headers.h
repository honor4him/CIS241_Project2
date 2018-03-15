#include <stdio.h>
#include <stdlib.h>

#ifndef __HEADERS_
#define __HEADERS_

char* displayMenu();
char* insert(char * product, char * unit, int price, int quan);
struct list* createList();
char* deleteProduct(char * product);
void clearList();
char* searchProduct(char * search);
char* displayAll();
char* purchase(char * product, int num);
char* sell(char * product, int num);

#endif
