// File:	Stack.c
// Author: 	James Alexander
// Purpose:	Implement a stack using linked list....reverse recursively

#include <stdio.h>
#include <stdlib.h>

struct stackNode {
	int data;
	struct stackNode *next;	
};
typedef struct stackNode *Node;

void push( Node *head_ref, int data );
int pop( Node *head_ref );
void display( Node *head_ref );
void reverse_recursive( Node *head_ref, Node prev, Node curr, Node next);
void reverse_iterative( Node *head_ref);

void reverse( Node *head_ref );
void print_recursive( Node *head );

int main( int argc, char *argv[] )
{
	// Create a list in memory
	Node head_ref = NULL;
	int i = 0;
	for( ; i <= 10; i++)
	 {
		 push( &head_ref, i );
	 }

	Node curr, prev, next;
	prev = NULL;
	curr = next = head_ref;
	

	//display(&head_ref);
	print_recursive( &head_ref);
	//reverse_iterative( &head_ref);
	//reverse_recursive( &head_ref, prev, curr, next );
	reverse( &head_ref );
	//display(&head_ref);
	print_recursive( &head_ref);
	
	return 0;
}

void push(Node *head_ref, int data )
{
	Node new_node = ( Node )malloc( sizeof(struct stackNode) );
	new_node->next = NULL;
	new_node->data = data;

	if( *head_ref == NULL ){
		*head_ref = new_node;
	} else {
		new_node->next = *head_ref;
		*head_ref = new_node;
	}

}

int pop( Node *head_ref )
{
	
	int return_this;	
	if( *head_ref == NULL )
	{
		printf("List is empty\n");
	}
	else
	{
		
		Node del = *head_ref;
		
		*head_ref = (**head_ref).next;
		return_this = (*del).data;
		free( del );
	}
	return return_this;
	
}
void print_recursive( Node *head_ref )
{
	if( *head_ref == NULL ) 
	{ 
		printf("\n\n");
		return;
	}
	printf( "%d ", (**head_ref).data );
	print_recursive( &(**head_ref).next );

}

void display( Node *head_ref )
{
	if( *head_ref==NULL )
	{
		printf("List is empty.\n");
		return;
	}
	Node temp = *head_ref;
	
	while( temp != NULL )
		{
		printf("%d ", temp->data );
		temp = temp->next;
	}
	printf("\n\n");

}

void reverse( Node *head_ref )
{
	// Split the list into two parts
	Node first;
	Node rest;
	if( *head_ref == NULL) return;
	first = *head_ref;
	rest = first->next;
	if( rest == NULL ) return;
	reverse( &rest );
	first->next->next = first;
	first->next = NULL;
	*head_ref = rest;
}

void reverse_iterative( Node *head_ref)
{
	Node curr, prev, next;
	prev = NULL;
	curr = next = *head_ref;
	
	while( curr != NULL )
	{
		next = (*curr).next;
		(*curr).next = prev;
		prev = curr;
		curr = next;
	}
	*head_ref = prev;
}


void reverse_recursive( Node *head_ref, Node prev, Node curr, Node next)
{
	if( curr != NULL ) {	// Check to see if current is not null
		// Solve subproblem of reversing the links and updating position
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;

		// Advance closer to terminating condition
		reverse_recursive( head_ref, prev, curr, next);
	} else {
		// Otherwise change the head reference to the last node pointed to by prev
		*head_ref = prev;
	}

}



