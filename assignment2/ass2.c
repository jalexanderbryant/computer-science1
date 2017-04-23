/*
* File: assignment2.c - Produce Database
* Author: James Alexander Bryant
* COP 3502 - Computer Science I 
* March 3rd, 2015
* Enjoy :)
*/

/*
 * Includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Structure Declaration
 */
struct produceItem {
	char produce[20];	// Item name
	char type[20];		// Item type
	char soldBy[20];	// Unit that item is sold by
	float price;		// Item Price
	int quantityInStock;	// Item quantity
	struct produceItem *next;	// Next element in list
};

// Define struct as a new type
typedef struct produceItem *Node;

/*
 * Function prototypes
 */

void create_inventory( Node *db_head, char *file_name );	// Create the inventory list from a file
void display_inventory( Node *db_head );	// Display the items in inventory
void reverse_inventory( Node *db_head );	// Reverse the inventory recursively
//void reverse_inventory( Node *db_head, Node prev, Node curr, Node next);	// Reverse the inventory recursively
void export_inventory( Node*db, char *file_name );	// Write the inventory to a file

// Helper functions
void push( Node *db_head, Node item );
void die( char *error_message, int option );


int main( int argc, char *argv[] )
{
	char input[BUFSIZ];	// Hold input string
	int input_as_int = 0;	// Convert to integer
	
	// Create inventory
	Node inventory = NULL;

	// Run indefinitely
	do {
		// Print instructions
		printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			"Inventory Options",
			"=================",
			"1. Stock Produce Department",
			"2. Display Produce Inventory",
			"3. Reverse Order of Produce Inventory",
			"4. Export Produce Inventory",
			"5. Exit Program",
			"Your selection: ");

		// Get input from user/keyboard
		if( fgets( input, BUFSIZ, stdin ) != NULL )
		{
			// convert to integer value
			input_as_int = atoi( input );

			// Validate
			if( (input_as_int == 0) || ( input_as_int > 5) )
			{
				die("Error: Enter a number between 1 and 5.\n", 0);
				// Start loop at beginning
				continue;
			}
		}
		
		// Helper nodes to reverse recursively
		Node prev, curr, next;
		curr = next = inventory;
		prev = NULL;

		// Input is valid
		switch( input_as_int )
		{
			case 1:
				create_inventory(&inventory, "AssignmentTwoInput.txt" );
				break;	
			case 2:
				display_inventory( &inventory );
				break;
			case 3:
				if( curr == NULL ) 
				{
					printf("Inventory is empty.\n");
					continue;
				}
				reverse_inventory( &inventory );
				printf("Inventory has been reversed.\n");
				break;
			case 4:
				export_inventory( &inventory, "AssignmentTwoOutput.txt" );
				break;
			case 5:
				die("Exiting program...", 1);
				break;
		
		}
			
	} while( 1 );

	return 0;
}



/*
 * Function definitions
 */

// Create Inventory from file
void create_inventory( Node *db_head, char *file_name )
{
	if( *db_head != NULL ) 
	{
		die("Inventory has been already created from the file.\n", 0);
		return;
	}

	// Attempt to open file for reading
	FILE *file_ptr = fopen( file_name, "r");
	if( file_ptr == NULL )
	{
		die("Error opening file. Make sure the file name is correct.\n", 0);
	}
	else 
	{
		// File Opened...lets get items from the file and 
		// add them to the inventory
		char line[ BUFSIZ ]; // Hold an incoming line

		// Go through entire file
		while( fgets( line, BUFSIZ, file_ptr ) != NULL )
		{
			// Node to hold the item before it goes in the list
			Node new_item = (Node)malloc( sizeof( struct produceItem) );
			(*new_item).next = NULL;
			char *in;
			//printf("%s\n", line);
			// Get the item name
			strtok( line, ",");

			// Add line to node
			strcpy( (*new_item).produce, line );

			// Get type and add to node
			in = strtok( NULL, ",");
			strcpy( (*new_item).type, in );

			// get soldBy and add to node
			in = strtok( NULL, "," );
			strcpy( (*new_item).soldBy, in );

			// Get price and save to node
			in = strtok( NULL, "," );
			(*new_item).price = atof( in );

			// Get quantity and save to node
			in = strtok( NULL, "," );
			(*new_item).quantityInStock = atoi( in );

			// Add item to inventory
			push( db_head, new_item );

		}
		
	}
	fclose( file_ptr );
	printf("Inventory has been created.\n");

} 

// Add item to list (push on stack)
void push( Node *db_head, Node item )
{
	if( *db_head == NULL )
	{
		*db_head = item;
	} else {
		(*item).next = *db_head;
		*db_head = item;
	}

}

// Display Inventory
void display_inventory( Node *db_head )
{
	// If no items in inventory
	if( *db_head == NULL ) 
	{
		printf("No items in inventory.\n");
		return;
	}
	
	Node temp = *db_head;
	printf("========================================================================\n");	
	printf(" %-8s%-15s%-15s%-15s%-10s%-10s\n",
		"Item #",
		"Produce",
		"Type",
		"Sold By",
		"Price",
		"In Stock");
	printf("========================================================================\n");
	int i = 1;
	while( temp != NULL )
	{
			printf(" %-8d%-15s%-15s%-15s%-10.2f%-10d\n",

			i,
			(*temp).produce,
			(*temp).type, 
			(*temp).soldBy, 
			(*temp).price, 
			(*temp).quantityInStock );
		temp = temp->next;
		i++;
	}
	printf("\n\n");
}

// This function reverses the linked list recursively.
/*void reverse_inventory( Node *db_head, Node prev, Node curr, Node next)
{
	if( curr != NULL )
	{
		next = (*curr).next;
		(*curr).next = prev;
		prev = curr;
		curr = next;
		reverse_inventory( db_head, prev, curr, next);
	} else {
		*db_head = prev;
	}
}*/
void reverse_inventory( Node *db_head )
{
	// Use these to split the list into two parts
	Node curr, rest;

	if( *db_head == NULL ) return;
	curr = *db_head;
	rest = curr->next;
	if( rest == NULL) return;
	reverse_inventory( &rest );
	curr->next->next = curr;
	curr->next = NULL;
	*db_head = rest;
}

// Write the inventory to the output file.
void export_inventory( Node *db_head, char *file_name)
{
	if( db_head == NULL ) die("No items to write to file.\n", 0);

	// Attempt to open file for reading
	FILE *file_ptr = fopen( file_name, "w");
	if( file_ptr == NULL )
	{
		die("Error opening file. Make sure the file name is correct.\n", 0);
	} else {
		
		
		Node temp = *db_head;
		fprintf( file_ptr,"%s", "========================================================================\n");	
		fprintf( file_ptr," %-8s%-15s%-15s%-15s%-10s%-10s\n",
		"Item #",
		"Produce",
		"Type",
		"Sold By",
		"Price",
		"In Stock");
		fprintf(file_ptr, "%s","========================================================================\n");
		int i = 1;
		while( temp != NULL )
		{
			fprintf(file_ptr, " %-8d%-15s%-15s%-15s%-10.2f%-10d\n",

			i,
			(*temp).produce,
			(*temp).type, 
			(*temp).soldBy, 
			(*temp).price, 
			(*temp).quantityInStock );
			temp = temp->next;
			i++;
		}
		fclose(file_ptr);
		printf("Inventory has been exported.\n");
	}
}

 // Terminate or display error message
void die( char *message, int option )
{

	printf("%s\n", message );
	if( option == 1 )
		exit(1);
}
