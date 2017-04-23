#include <stdio.h>
#include <stdlib.h>
#include <time.h>	// This is new???

#define EXTRA 10	//

int *make_dynamic_array( int n );
int *increase_array_size( int *array, int original_size, int extra);
int main()
{
	int numVals;	// Holds input from the user

	srand( time(0 ) ); // Used with rand() to generate random vals

	printf("How many numbers do you want to pick?\n");
	scanf("%d", &numVals );	// get input from user
	
	// Allocate space in memory for n integer values. Where n=numVals
	// More specifically, allocate space for an array of ints where
	// the size is given by the user input.
	//int *values = (int*)malloc(numVals * sizeof(int));
	int *values = make_dynamic_array( numVals );
	int i = 0;
	// Generate random values for each position in the array
	for( i = 0; i < numVals; i++)
	{
		values[i] = rand()%100;
	}
	
	// Print the values of the array
	for( i = 0; i < numVals; i++ )
		printf("%d ", values[i]);
	printf("\n");

	// Lets extend the array to be able to include 10 extra ints.
	// They'll be initialzed to 0s
	//values = (int *)realloc(values, (numVals+EXTRA)*sizeof(int));
	values = increase_array_size( values, numVals, EXTRA);

	// Print the new list
	for( i = 0; i < numVals+EXTRA; i++ )
		printf("%d ", values[i]);
	printf("\n");
	
	// Insert 10 new random values into the array
	for(i = 0; i<EXTRA; i++)
		values[numVals+i] = rand()%100;
	numVals += EXTRA;

	// print once more 
	for( i = 0; i < numVals; i++ )
		printf("%d ", values[i]);
	printf("\n");
	
	// Cleanup and free the memory space.
	free(values);
	return 0;
}

int *make_dynamic_array( int n )
{
	return (int*)malloc(n*sizeof(int));
}

int *increase_array_size( int *array, int original_size, int extra)
{
	array = (int*)realloc( array, (original_size+extra)*sizeof(int));
	return array;
}
