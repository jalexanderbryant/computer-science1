/* File: AssignmentFour.c
 * Author: James A. Bryant
 * Date: April 9th, 2015
 * Course: COP 3502 - Computer Science
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	BUFSIZE 100

// Node used in Binary Tree
struct binTreeNode
{
	int data;
	struct binTreeNode *right;
	struct binTreeNode *left;
};
// Make my life easier with the following...
typedef struct binTreeNode *Node;


struct queueNode
{
	Node treeElement;	 // Data contents
	struct queueNode *next;
};
typedef struct queueNode *QNode;


// General Prototypes
int get_user_input();
void die( char *str );
void generate_BST( Node *tree_root, char *input_file );
Node create_BST_node( int data );
void insert_into_tree( Node *root, Node insert);
void print_preorder( Node *root );
void print_inorder( Node *root );
void print_postorder( Node *root );
void breadth_first_traversal( Node tree_root );
void find_tree_median( Node tree_root );
int tree_sum( Node *root );
Node delete_from_tree( Node root, int key );


//Auxiliary Prototypes
int isEmpty( Node root );
int isLeaf( Node node );
int count_tree_nodes( Node *root );
Node findNode( Node current_node, int key );
Node findParent( Node root, Node node);
Node findMinValue( Node root );
Node findMaxValue( Node root );
int hasOnlyRightChild( Node node );
int hasOnlyLeftChild( Node node );

// Queue Prototypes
QNode create_queue_node( Node tree_node );	// 
QNode qFront( QNode *Qhead );				// get front node w/out deleting
void qPush( QNode *Qhead, Node insert );	// Add node to end
void qPop( QNode *Qhead );					// Delete node from front
int isQueueEmpty( QNode *Qhead );			// Check if queue is empty

char *instructions[] = {
	"\n\n=============================",
	"1) Generate Binary Search Tree",
	"2) Print the BST in pre-order format",
	"3) Print the BST in in-order format",
	"4) Print the BST in post-order format",
	"5) Print the BST in breadth-first format",
	"6) Find a value in the BST",
	"7) Find the minimum value in the BST nodes",
	"8) Find the maximum value in the BST nodes",
	"9) Calculate the average value of the BST nodes",
	"10) Find the median value of the BST nodes",
	"11) Calculate the sum of the BST nodes",
	"12) Count the number of BST nodes",
	"13) Delete a value in the BST",
	"14) Exit Program",
	"\n=============================\n"
};


int main( int argc, char *argv[] )
{
	Node my_first_tree = NULL;	// Create a tree
	Node temp = NULL;			// helper node
	int user_input;				// Hold user input
	int i = 0;					// loop index
	int avg = 0;				// average value
	int med = 0;

	// Print the options/instructions
	for( i = 0; i < 16; i++ ) 
	{
		printf("%s\n", instructions[i] );
	}

	// Launch an infinite loop
	do
	{
		
		// Prompt for input
		printf("\n\nMake a selection: ");
		user_input = get_user_input();

		// validate user_input
		if( (user_input < 1) || (user_input > 14) )
		{
			printf("Bad input, try again.\n");
			continue;
		}
		
		// Check user-input for next step
		switch( user_input )
		{
			case 1:
				// Case 1 - Generate binary search tree from file				
				generate_BST( &my_first_tree, "AssignmentFourInput.txt" );
				printf("Tree has been generated\n\n");
				break;
			case 2:
				// Case 2 - Print the BST in Pre-Order format
				if( isEmpty(my_first_tree) ) continue;

				printf("Pre-Order Format: \n");
				print_preorder( &my_first_tree );
				break;
			case 3:
				// Case 3 - Print the BST in In-Order format
				if( isEmpty(my_first_tree) ) continue;

				printf("In-Order Format: \n");
				print_inorder( &my_first_tree );
				break;
			case 4:
				// Case 4 - Print the BST in Post-Order format
				if( isEmpty(my_first_tree) ) continue;

				printf("Post-Order Format: \n");
				print_postorder( &my_first_tree );
				break;
			case 5:
				if( isEmpty(my_first_tree) ) continue;
				
				// Case 5 - Print the BST in breadth-first format
				breadth_first_traversal( my_first_tree );
				break;
			case 6:
				// Case 6 - Find a value
				if( isEmpty(my_first_tree) ) continue;

				printf("Enter a value to search for: ");
				user_input = get_user_input();
				temp = findNode( my_first_tree, user_input );
				
				if ( temp == NULL )
					printf("%d not found in Tree.\n", user_input);
				else
					printf( "%d found in tree.", user_input );
				
				break;
			case 7:		
				// Case 7 - Find the smallest value in the tree.
				if( isEmpty(my_first_tree) ) continue;

				temp = findMinValue( my_first_tree );

				printf("The smallest value in the tree is: %d\n", (*temp).data);
				break;
			case 8:
				// Case 8 - Find the largest value in the tree
				if( isEmpty(my_first_tree) ) continue;

				temp = findMaxValue( my_first_tree );
				
				printf("The largest value in the tree is: %d\n", (*temp).data);
				break;
			case 9:
				// Case 9 - Calculate the average value of the BST nodes
				if( isEmpty(my_first_tree) ) continue;

				avg = tree_sum(&my_first_tree) / count_tree_nodes(&my_first_tree);

				printf("The average value in the tree \n\t(as an integer): %d\n\t(as a decimal): %.2f", 
					avg,
					(double)tree_sum(&my_first_tree) / count_tree_nodes( &my_first_tree )
				 );
				break;
			case 10:
				// Case 10 - Find the median value of the BST nodes
				if( isEmpty(my_first_tree) ) continue;
				//find_tree_median( my_first_tree );
				printf("Function undefined.\n");
				break;
			case 11:
				// Case 11 - Sum the nodes in the tree
				if( isEmpty(my_first_tree) ) continue;

				printf("Sum of the nodes in the Tree: %d\n", count_tree_nodes( &my_first_tree ) );
				break;

			case 12:
				// Case 12 - Count the number of nodes in the tree
				if( isEmpty(my_first_tree) ) continue;			// Are there nodes in the tree?

				printf("There are %d nodes in the tree.\n", count_tree_nodes( &my_first_tree) );
				break;
			case 13:
				// Case 13 - Delete a node from this tree
				printf("Insert a value to delete: ");
				user_input = get_user_input();

				temp = findNode( my_first_tree, user_input );
				
				if ( temp == NULL )
					printf("%d not found in Tree.\n", user_input);
				else
				{
					delete_from_tree( my_first_tree, user_input );
					printf( "%d was deleted from tree.\n", user_input );
				}

				break;
			case 14:
				// Case 14 - Terminate execution
				printf("Thanks for participating\n");
				exit(1);
		}
	}
	while( 1 );
	return 0;
}

int get_user_input()
{
	// Get user input
	char input[BUFSIZE];;
	int converted;
	char *p;
	if( fgets( input, BUFSIZE, stdin ) != NULL );
	
	// convert
	converted = atoi( input );

	return converted;
}


void generate_BST( Node *tree_root, char *input_file )
{
	// Holds incoming data from file
	int data;

	// Check if file has already been read
	if( *tree_root != NULL )
	{
		printf("File has already been read from.\n");
		return;
	}

	// Open file for reading, if possible
	FILE *file_ptr = fopen(input_file, "r");
	if( file_ptr == NULL )
	{
		die("Error opening file. Make sure the file name is correct\n");
	}
	else
	{
		// File has been opened. Let's read from it.
		while( fscanf( file_ptr, "%d", &data ) != EOF )
		{
			// Create a new node
			Node new_node = create_BST_node( data );
			// Insert a new node
			insert_into_tree( tree_root, new_node);
		}
	}
} // End generate_BST

Node create_BST_node( int data )
{
	Node temp = (Node)malloc( sizeof( struct binTreeNode) );
	(*temp).data = data;
	(*temp).right = NULL;
	(*temp).left = NULL;
	return temp;
} // End create_BST_node



void insert_into_tree( Node *root, Node insert)
{
	if( *root == NULL)
	{
		*root = insert;
		return;
	}
	else 
	{
		if( (*insert).data > (**root).data )
			insert_into_tree( &((**root).right), insert );
		else
			insert_into_tree( &((**root).left), insert);
	}
} // insert_into_tree()


void print_preorder( Node *root )
{
	if( *root != NULL )
	{
		printf("%d ", (**root).data );	
		print_preorder( &((**root).left) );
		print_preorder( &((**root).right) );
	}
} // print_preorder()


void print_inorder( Node *root )
{
	if( *root != NULL )
	{
		print_inorder( &((**root).left) );
		printf("%d ", (**root).data );	
		print_inorder( &((**root).right) );
	}
} // print_inorder()


void print_postorder( Node *root )
{
	if( *root != NULL )
	{
		print_postorder( &((**root).left) );
		print_postorder( &((**root).right) );
		printf("%d ", (**root).data );	
	}
} // print_postorder()


int tree_sum( Node *root )
{
	if( *root == NULL )
		return 0;
	else
		return (**root).data + tree_sum( &((**root).left) ) + tree_sum( &((**root).right) );
} // tree_sum()


void die( char *str )
{
	printf("%s\n", str);
	exit(1);
} // die()

/** Auxiliary Functions **/
int isEmpty( Node root )
{
	if( root == NULL ) {
		printf("Tree is empty.\n\n");
		return 1;
	}
	else 
		return 0;			
}


Node findNode( Node current_node, int key )
{
	if( current_node != NULL )
	{
		// Value found?
		if( current_node->data == key )
			return current_node;

		if( key < current_node->data )	// search to the left
			return findNode( current_node->left, key );
		else								// search to the right
			return findNode( current_node->right, key);
	}
	else
	{
		return NULL;	// Value not found in tree
	}
} // findNode()

Node findParent( Node root, Node node)
{
	// Address NULL cases
	if( (root == NULL) || ( root == node ) )
		return NULL;

	// If the root is the direct parent of the node.
	if( (*root).left == node || (*root).right == node )
		return root;

	// Look for node's parent in the left side of the tree.
	if( (*node).data < (*root).data )
		return findParent( (*root).left, node);

	//  Look for node's parent in the right side of the tree.
	else if( (*node).data > (*root).data )
		return findParent( (*root).right, node );

	// Address any extraneous cases
	return NULL;
} // findParent()

Node findMinValue( Node root )
{
	// If the root holds the minimum value.
	if( (*root).left == NULL )
		return root;
	else
		// Minimum value is in the left subtree of the root
		return findMinValue( (*root).left );
} // findMinValue

Node findMaxValue( Node root )
{
	// If the root holds the largest value.
	if( (*root).right == NULL )
		return root;
	else
		// Largest value is in the right subtree of the root
		return findMaxValue( (*root).right );
} // findMaxValue

int isLeaf( Node node )
{
	// Return 1 if node is a leaf node, oth. return 0
	return ( ((*node).left == NULL)  && ((*node).right == NULL) );
} // isLeaf()

int count_tree_nodes( Node *root )
{
	// Return 0 if current node is NULL
	// Otherwise add 1 to the total
	if( *root == NULL )
		return 0;
	else
		return 1 + count_tree_nodes( &((**root).left) ) + count_tree_nodes( &( (**root).right));
} // end count_tree_nodes()


int hasOnlyRightChild( Node node )
{
	// Return 1 if node has a right child and no left child
	// Return 0 otherwise
	return( ( node->left == NULL ) && ( node->right !=NULL ) );
} // end hasOnlyRightChild

int hasOnlyLeftChild( Node node )
{
	// Return 1 if node has a left child and no right child
	// Return 0 otherwise
	return( ( node->right == NULL ) && ( node->left !=NULL ) );
}



/** Queue Functions - for breadthfirst traversal. **/
QNode create_queue_node( Node tree_node )
{
	QNode temp = (QNode)malloc( sizeof( struct queueNode ) );
	(*temp).treeElement = tree_node;
	(*temp).next = NULL;
	return temp;
} // End create_BST_node


void qPush( QNode *Qhead, Node insert )
{
	QNode new_node = create_queue_node( insert );	// Create a new node to
													// enqueue
	if( *Qhead == NULL )	// Check for empty tree
	{
		*Qhead = new_node;	// Point Qhead to new node
		return;
	}
	else					
	{
		// If the queue has actual values
		QNode temp = *Qhead;		// Used for traversal

		// Traverse to end of Queue
		while( (*temp).next != NULL )
			temp = (*temp).next;

		// Enqueue new node
		(*temp).next = new_node;
	}

} // end enqueue()

void qPop( QNode *Qhead )
{
	QNode del = NULL;
	// Check for empty queue
	if( *Qhead == NULL )
		return;

	// If queue has values
	del = *Qhead;			// Point to head of Queue
	*Qhead = (**Qhead).next;	// Point head to next node
	free(del);					// Remove first node

} // end dequeue()


int isQueueEmpty( QNode *Qhead )
{
	if( *Qhead == NULL )
		return 1;
	else
		return 0;
} // end isQueueEmpty



QNode qFront( QNode *Qhead ) 
{
	if(*Qhead == NULL )
	{
		printf("Queue is empty. \n");
	}
	else
	{
		QNode temp = *Qhead;
		return temp;
	}
}



void breadth_first_traversal( Node tree_root )
{
	if( tree_root == NULL ) return;
	QNode qhead = NULL;
	qPush( &qhead, tree_root );

	while( isQueueEmpty(&qhead) != 1 )
	{
		QNode current = qFront( &qhead );
		printf("%d ", current->treeElement->data );

		if( current->treeElement->left !=NULL ) qPush( &qhead, current->treeElement->left );
		if( current->treeElement->right !=NULL ) qPush( &qhead, current->treeElement->right);

		qPop( &qhead );
	}
} // end breadth_first_traversal()


/*** Delete from tree ***/
// Delete the node containing key and return the new root
Node delete_from_tree( Node root, int key )
{
	// base
	if (root == NULL) return root;

	if( key < (*root).data )
		(*root).left = delete_from_tree( (*root).left, key );

	else if( key > (*root).data )
		(*root).right = delete_from_tree( (*root).right, key );

	else	// Found the node containing the key
	{
		// node w/ only left child...
		if( (*root).left == NULL )
		{
			Node temp = (*root).right;
			free(root);
			return temp;
		}
		else if ( (*root).right == NULL )
		{
			Node temp = (*root).left;
			free(root);
			return temp;
		}

		// If a node has 2 children, replace it largest value in left subtree
		Node temp = findMaxValue( (*root).left );
		(*root).data = (*temp).data;

		(*root).left = delete_from_tree( (*root).left, (*temp).data );
	}
	return root;
}



// Get median using Morris Traversal
// Incomplete Function....
void find_tree_median( Node tree_root )
{
	Node curr, prev;
	if( tree_root == NULL )
		return;

	// Otherwise if there are nodes
	int len = count_tree_nodes( &tree_root ); // Get number of nodes
	printf(" **%d\n", len);


	curr = tree_root;

	while( curr != NULL )
	{
		// Insert into array
		if( (*curr).left == NULL  )
		{
			printf("%d ", (*curr).data );
			curr = (*curr).right;
		}
		else
		{
			// Find the inorder predecessor of current node
			prev = (*curr).left;
			while( ((*prev).right != NULL) && ((*prev).right != curr) )
				prev = (*prev).right;

			// Make current the right child of its inorder predecessor
			if( (*prev).right == NULL )
			{
				(*prev).right = curr;
				curr = (*curr).left;
			}
			else
			{
				// Reverse the changes made in the IF portion to restore original tree
				(*prev).right = NULL;
				printf("%d ", (*curr).data );
				curr = (*curr).right;
			}
		}
	}
}