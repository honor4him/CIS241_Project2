#include <stdio.h>
#include <stdlib.h>
#include "headers.h"


struct list{
	char * product;
	char * unit;
	int price;
	int quan;
	struct list *next;

};

typedef struct list LIST;

LIST *head;

int main(int argc, char * argv[]){
	
	// Choice delcared to 0
	int choice = 0;	
	do{

		printf("%s", displayMenu());
		scanf("%d", &choice);

		//Cases
		// Create list
		if(choice == 1){
			LIST *head = createList();
		}
		
		// Insert a product
		else if(choice == 2){
			
		}




	} while(choice != 0);	

	return 0;
};

 char* displayMenu(){
	return 
"\n	1: Create an empty list    2: Insert a product\n\
	3: Delete a product        4: Delete entire list\n\
	5: Search a product        6: Display products in the listn\n\
	7: Purchase a product      8: Sell a product\n\
	9: Save to file            0: Exit\n\n";
		
}
                
char* insert(char * product, char * unit, int price, int quan){

}
 
struct list* createList(){
	return (LIST*)malloc(sizeof(LIST));	
}
                 
char* deleteProduct(char * product){

}

void clearList(){

}
                  
char* searchProduct(char * search){

}
 
char* displayAll(){

}
                
char* purchase(char * product, int num){

}

char* sell(char * product, int num){

} 
