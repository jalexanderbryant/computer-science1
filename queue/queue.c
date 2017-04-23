#include <stdio.h>
#include <stdlib.h>

struct queueElement
{
	int data;
	struct queueElement *next;
};

typedef struct queueElement *Node;

void enqueue( Node *head_ref, int data )
{
	// Insert an element at the rear of the queue
	Node new = (Node)malloc( sizeof(struct queueElement) );
	new->next = NULL;
	new->data = data;

	if( *head_ref == NULL ) {// place at head
		*head_ref = new;
	}
	else 
	{
		Node temp = *head_ref;
		while( temp->next != NULL )
			temp=temp->next;

		temp->next = new;
	}
}

void dequeue( Node *head_ref )
{
	if( *head_ref == NULL )
	{
		printf("No items in queue\n");
		return;
	}

	Node temp = *head_ref;
	*head_ref = (**head_ref).next;

	free( temp );
}
void display( Node *head_ref )
{
	if( *head_ref == NULL ) {
		printf("No elements in the queue\n");
	}
	else
	{
		Node temp = *head_ref;
		while( temp != NULL ) 
		{
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}
void peek( Node *head_ref )
{
	if(*head_ref == NULL)
	{
		printf("No items in queue\n");
		return;
	}

	printf(" The element at the front of the queue is %d\n",
		(**head_ref).data);
}

int isEmpty( Node *head_ref )
{
	if( *head_ref == NULL )
		return 1;
	else
		return 0;
}

void clear( Node *head_ref )
{
	if( isEmpty( head_ref ) == 0 ) // has values
	{
		Node temp = *head_ref;
		while( temp != NULL )
		{
			*head_ref = (**head_ref).next;
			temp = *head_ref;
			free(temp);
		}
	}
}

int main( int argc, char *argv[] )
{
	Node queue_start = NULL;
	int i = 0;
	for( ; i < 5; i++ )
	{
		enqueue( &queue_start, i);
	}

	display( &queue_start );
	peek( &queue_start);
	dequeue( &queue_start );
	display( &queue_start);
	peek( &queue_start);

	clear( &queue_start );
	display( &queue_start );
	
	return 0;
}


