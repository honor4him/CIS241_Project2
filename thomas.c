#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

/*
This program is a management system using linked lists. A user is prompted
to enter 4 sources of information for every inventory item. The product name,
the unit of type, the price and the quantity of items on hand.

Author: Zachary Thomas
Version: 1.0
Date: 3-15-18
*/

// Define LIST
typedef struct list LIST;

// Begin main
int main(int argc, char * argv[]){

	// Used to determine if a list has been created
	int listCreated = 0;

	// Two placeholder variables to manipulate the list
	LIST * head = NULL;
	LIST * temp = NULL;

	// Placeholders to insert into list and search
	char tempProduct[20], tempUnit[20], search[20];
	int priceTemp, quanTemp;

	// Choice delcared to 0. Begin main loop
	int choice = 0;
	do{

		// Show menu to determine user's choice
		displayMenu();
		scanf("%d", &choice);

		//Cases

		// Create list
		if(choice == 1){

			// See if list has been created already
			if(listCreated == 0){
				head = createList();
				listCreated = 1;

			// Delete old list if there is one
			} else if(listCreated == 1){
				printf("\nList is being deleted . . .\n");
				clearList(head);
				listCreated = 0;
			}

		}

		//Make sure list has been created
		if(listCreated == 1){

			// Insert a product
			if(choice == 2){
				printf("\nPlease enter product name, unit, price, and quantity: ");
				scanf("%s %s %d %d", tempProduct, tempUnit, &priceTemp, &quanTemp);

				// See if price or quan is more than 0
				if(priceTemp <= 0 || quanTemp <= 0){
					printf("\n--==Price and quantity must be greater than 0==--\n");
					continue;
				}

				// See if product exists
				temp = searchProduct(head, tempProduct);

				// If product does not exist, add to list
				if(temp == NULL){
					temp = createAtTail(head, temp); //(LIST*)malloc(sizeof(LIST));
					strcpy(temp->product, tempProduct);
					strcpy(temp->unit, tempUnit);
					temp->price = priceTemp;
					temp->quan = quanTemp;
					printf("\n");
				} else {
					printf("\n\n--==Product already exists==--\n\n");
				}
			}

			// Delete a product
			else if(choice == 3){
				printf("\nPlease enter the product name to delete: ");
				scanf("%s", tempProduct);
				printf("\n");
				deleteProduct(head, tempProduct);
			}

			// Delete entire list
			else if(choice == 4){
				printf("\nList is being deleted . . .\n");
				clearList(head);
				listCreated = 0;
			}

			// Find a product
			else if(choice == 5){
				printf("\nPlease enter the name of the product: ");
				scanf("%s", search);
				printf("\n");
				temp = searchProduct(head, search);
				if(temp == NULL)
					printf("\n\n---== Product not found ==---\n\n");
			}

			// Print whole list
			else if(choice == 6){
				displayAll(head);
			}

			// Purchase a product
			else if(choice == 7){
				printf("\nPlease enter the product name to purchase: ");
				scanf("%s", search);
				printf("\n");
				purchase(head, search);
			}

			// Sell a product
			else if(choice == 8){
				printf("\nPlease enter the product to sell: ");
				scanf("%s", search);
				printf("\n");
				sell(head, search);
			}

			// Save to file
			else if(choice == 9){
				saveFile(head);
			}

		// Tell user list has not been created
		} else {
			printf("\n\n--List has not been created yet. Please select 1.--\n\n");
		}

	} while(choice != 0);

	// Delete list
	clearList(head);
	return 0;
};

// Display entire menu
void displayMenu(){
	printf("\n	1: Create an empty list    2: Insert a product\n\
	3: Delete a product        4: Delete entire list\n\
	5: Search a product        6: Display products in the list\n\
	7: Purchase a product      8: Sell a product\n\
	9: Save to file            0: Exit\n\n");
}

// Create the head node for the list
LIST * createList(){
	LIST * head = (LIST*)malloc(sizeof(LIST));
	head->next = NULL;
	return head;
}

// Delete a product from the list
void deleteProduct(LIST * head, const char * product){

	// Temp node to free later
	LIST * temp = searchProduct(head, product);

	// If product searching for doesn't exist
	if(temp == NULL){
		printf("\n\n---== Product not found ==---\n\n");
		return;
	}
	// Get node before search
	while(head->next != temp){
		head = head->next;
	}

	// Make next pointer null if does not exist
	if(head->next->next != NULL){
		head = head->next->next;
	} else {
		head->next = NULL;
	}

	// Delete node
	free(temp);

	// Verify
	printf("\n%s has been deleted.\n\n", product);
}

// Recursively delete list
void clearList(LIST * head){
	if(head != NULL){
		clearList(head->next);
		free(head);
	}
}

// Function used to search the list
LIST * searchProduct(LIST * head, const char * search){

	// Don't search head
	head = head->next;

	// Begin loop, return if found, otherwise will say not found.
	while (head!=NULL) {
		// Compare product names with search
		if((strcmp(head->product, search)) == 0){
			printf("\n\n--Product Found--\n\n");

			// Send to display to screen
			toString(head);

			// Used in deleting product
			return head;
		} else {
			// If not found in current iteration
			head = head->next;
		}
	}

	// If product is not found
	return NULL;
}

// Display all items in list
void displayAll(LIST * head){

	// Skip head because head has no information other than a pointer
	head = head->next;

	// Header
	printf("\n\n\n---== All products in list ==---\n\n");

	// Print all products
	while(head!=NULL){
		toString(head);
		head = head->next;
	}
}

// Purchase 1 item
void purchase(LIST * head, char * product){
	LIST * temp = searchProduct(head, product);
	// Increase by 1 if temp exists
	if(temp != NULL){
		temp->quan++;
	} else {
		printf("\n\n---== Product not found ==---\n\n");
	}
}

// Sell 1 item, delete from list if there is only 1 product left
void sell(LIST * head, char * product){
	LIST * temp = searchProduct(head, product);

	// If product is not found
	if(temp == NULL){
		printf("\n\n---== Product not found ==---\n\n");
	}

	// Decrease if temp exists
	if(temp != NULL){
		// Delete if resulting sell is 0
		if(temp->quan == 1){
			deleteProduct(head, product);
		} else {
			// Decrease by 1
			temp->quan--;
		}
	}
}

// Creates a node at the tail of the list
LIST * createAtTail(LIST * head, LIST * temp){

	// Loop through list and then add at end
	while(head->next != NULL){
		head = head->next;
	}
	temp = (LIST*)malloc(sizeof(LIST));
	head->next = temp;
	temp->next = NULL;
	return temp;
}

// Prints the node to the screen
void toString(LIST * temp){
	printf("Product: %s\nUnit: %s\nPrice: %d\n\
Quantity: %d\n\n", temp->product, temp->unit, temp->price, temp->quan);
}

// Save current list to file
void saveFile(struct list * head){
	// Skip head
	head = head->next;

	// Create variables for saving to file
	FILE *out;
	out = fopen("output.txt", "w");

	// If file can't be created
	if(out == NULL){
		printf("File could not be created.\n\n");
		return;
	}

	// Go through each node
	while(head != NULL){
		// Output to FILE
		fprintf(out, "Product: %s\nUnit: %s\nPrice: %d\n\
Quantity: %d\n\n", head->product, head->unit, head->price, head->quan);

		head = head->next;
	}

	fclose(out);
	printf("\n\n--==Product list saved succesfully==--\n\n");
}
