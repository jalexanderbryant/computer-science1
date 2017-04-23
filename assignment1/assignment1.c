/* File: 	assignment1.c - Linked List Database
 * Author:	James Alexander Bryant
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Node Element
struct NodeElement{
	char name[50];		// student name
	int id;			// student id
	struct NodeElement *next;	// points to next element
};

// Define struct NodeElement as a new type
typedef struct NodeElement *Node;

/* Function Prototypes */
Node read_file(Node db_head );
Node insert( Node db_head ); 
void display( Node db_head );
Node delete_by_id( Node db_head);
Node delete_by_name( Node db_head);
Node create_node();
Node add_to_list( Node db_head, Node insert );
void die( char *error_message );

int main( int argc, char *argv[] )
{

	// Variables to hold input, and...
	char input[BUFSIZ];
	// ..input converted to an integer value
	int input_as_int;

	// Linked list head
	Node database = NULL;

	// Read files into Linked list
	database = read_file( database );
	
	do {
		// Print instructions
		printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			"Select from the options below:",
			"1: Insert",
			"2: Display",
			"3: Delete By ID",
			"4: Delete By Name",
			"5: Exit",
			"Your selection: " );
		
		// Collect input from keyboard
		if( fgets( input, BUFSIZ, stdin) != NULL )
		{
			// convert input to integer
			input_as_int = atoi( input );

			// Validate that input is between 0 and 1
			if( (input_as_int < 1) || (input_as_int > 5))
			{
				// Provide error message
				printf("Error: Enter a number between 1 and 5.\n");
				// Repeat loop from the the beginning
				continue;
			}
		}
		
		// If input is good
		switch ( input_as_int )
		{
			case 1:
				database = insert( database );
				break;
			case 2:
				display( database );
				break;
			case 3:
				database = delete_by_id( database );
				break;
			case 4:
				database = delete_by_name( database );
				break;
			case 5:
				die("Exiting program...");
				break;
		} // end switch()
	} while ( 1 );	// Ensure the program runs indefinitely
	
	return 0;
} // End main()

Node insert( Node db_head )
{
	char user_input[BUFSIZ];	// Hold input from user

	Node new_node = create_node();	// Create a new node

	// Check to see if allocation was successful
	if( new_node == NULL )
	{
		printf("**Error creating database item.\n");
		return db_head;
	}
	
	// Prompt user for a name
	printf("Enter a name for student: ");

	// Collect name from user
	if( fgets( user_input, BUFSIZ, stdin) != NULL )
	{
		// Remove newline character from end of string
		char *c;
		if( (c = strchr(user_input, '\n')) != NULL )
			*c = '\0';
		
		// copy user name to node's name field
		strcpy( new_node->name, user_input);
		
		// Prompt user for an ID
		printf("Enter an ID for the student: ");
		
		// Collect input from user
		fgets( user_input, BUFSIZ, stdin);

		// Add id to new node
		new_node->id = atoi(user_input);
	}
	else
	{
		// If an error occurs when reading input
		printf("**Error accepting Student name.\n");
		return db_head;
	}
	
	// Add element to the database
	db_head = add_to_list( db_head, new_node);
	
	// Print success message
	printf("Added student %s with ID number %d\n",
		new_node->name, new_node->id);

	return db_head;
}

void display( Node db_head )
{
	// Return if there are no items in the list
	if( db_head == NULL )
	{
		printf("**There are no items to display\n");
		return;
	} else {
		
		Node temp = db_head;		// Temporary node for traversing

		// Header
		printf("\n%-50s%s\n", "Name", "Student ID");
		printf("-----------------------------------------------------------\n");

		// Traverse the list and print the items to the screen
		while( temp != NULL )
		{
			printf("%-50s%d\n", temp->name, temp->id);
			temp=temp->next;
		}
	}
}


Node delete_by_id( Node db_head)
{
	// If there are no elements, return
	if( db_head == NULL )
	{
		printf("** Database is empty.\n");
		return db_head;
	}

	char user_input[BUFSIZ];
	int id;
	// Prompt user for id
	printf("Enter an ID to be deleted: ");
	
	// Collect input from user
	fgets(user_input, BUFSIZ, stdin);
	// Convert input to integer value
	id = atoi(user_input);

	Node curr = db_head;
	Node prev = NULL;
	int found_flag = 0;	// flag =1 if ID exists in list
				// flag = 0 if ID is not in list
	
	// Check to see if first node's ID is a match
	if( db_head->id == id )
	{
		found_flag = 1;			// ID found in list
		db_head = db_head->next;	// Update head of list
		free(curr);			// Remove original head
	} else {
		//traverse the list in search of the given ID
		while( curr != NULL )
		{
			// stop on node containing ID
			if(curr->id == id)
			{
				prev->next = curr->next;
				found_flag = 1;
				free( curr );
				break;
			}
			
			// Traverse by updating previous and curr
			prev = curr;
			curr = curr->next;
		}
	}

	// Print result
	if( !found_flag)
	{
		printf("\n**ID of %d was not found in database.\n", id);
	} else {
		printf("\nEntry with ID of %d sucessfully deleted.\n", id);
	}

	return db_head;
}


Node delete_by_name( Node db_head)
{
	// Check to see if there are item in database
	if( db_head == NULL )
	{
		printf("**There are no items in database.\n");
		return db_head;
	}

	// If there are items in list
	char user_input[BUFSIZ];
	int found_flag = 0;
	char *c;
	
	// Helper nodes
	Node curr = db_head;
	Node prev = NULL;

	// Prompt user for input...
	printf("Enter the full name of the student you want to delete: ");

	// Get name from user; On failure to read input, return head
	if( fgets(user_input, BUFSIZ, stdin) == NULL )
	{
		printf("**Invalid user input**");
		return db_head;
	}
	
	// Remove newline char from input if it's there
	if( (c = strchr(user_input, '\n') ) != NULL )
		*c = '\0';	// replace it with null char

	
	// Check to see if the name is in the first node
	if( strcmp(db_head->name, user_input) == 0)
	{
		db_head = db_head->next;
		found_flag = 1;
		free(curr);
	} else {
		
		// Traverse the list to find the correct ID
		while( curr != NULL )
		{
			if( strcmp( curr->name, user_input) == 0 )
			{
				prev->next = curr->next;
				found_flag = 1;
				free( curr );
				break;
			}
			// Traverse by updating prev and curr
			prev = curr;
			curr = curr->next;
		}
	}
	
	if( !found_flag )
	{
		printf("\n%s was not found in the database.\n", user_input);
	} else {
		printf("\n%s successfully deleted from the database.\n", user_input);
	}
	// Return head
	return db_head;
}


Node read_file( Node db_head )
{
	
	// Open file for reading
	FILE *file_ptr = fopen( "AssignmentOneInput.txt", "r" );
	char line[BUFSIZ];
	char *c;
	
	// If the file cannot be read, exit the program with error messsage
	if( file_ptr == NULL ) die("**Error reading from file.");

	while( fgets( line, BUFSIZ, file_ptr ) != NULL )
	{
		// Create a temporary node
		Node new_node = create_node();

		// Get the name from the string
		strtok( line, ",");

		// Add line to the Node
		strcpy( new_node->name, line);
		
		// Collect ID from string
		c = (char *)strtok( NULL, ",");
		new_node->id = atoi( c );
		
		// add node to list
		db_head = add_to_list( db_head, new_node );
	}
	
	
	return db_head;
}

// Helper function to create a new node
Node create_node()
{
	Node new_node = (Node )malloc( sizeof(struct NodeElement) );
	new_node->next = NULL;
	return new_node;
}

// Helper function to insert a node
Node add_to_list( Node db_head, Node insert )
{
	// Add node to end of list
	Node temp = db_head;
	if( temp == NULL)
	{
		db_head = insert;
	}
	else 
	{
		while( temp->next != NULL )
			temp = temp->next;

		temp->next = insert;
	}
	
	return db_head;
}

// Helper function to terminate with error
void die( char *error_message )
{
	printf("**%s\n", error_message);
	exit(1);
}
