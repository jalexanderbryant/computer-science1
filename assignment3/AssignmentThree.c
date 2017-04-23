/*
 * File: 	AssignmentThree.c
 * Course:	COP 3502 (Computer Science 1)
 * Author: 	James A. Bryant
 * Date: 	3/27/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	BUFSIZE 100	// Create a maximum size for an incoming line

// Prototypes
void ExchangeChars(char str[], int i, int j);
void CreatePermutations(char str[], int fixed, FILE *output_file);
void die( char *error_message );


int main( int argc, char *argv[] )
{
	// Open file for reading
	FILE *input_ptr = fopen("AssignmentThreeInput.txt", "r");
	printf("Attempting to open input file.\n\n");

	// Terminate program if file cannot be opened
	if( input_ptr == NULL ) die("Error reading input file.");
	printf("Input file now open: \n\n");
		
	// Open a file for writing
	FILE *output_ptr = fopen("AssignmentThreeOutput.txt", "w");

	// Hold single line from input file
	char line[BUFSIZE];
	// Temp char to clear newline character
	char *c;

	// Read input from file, line by line
	while(fgets( line, BUFSIZE, input_ptr ) != NULL )
	{
		// Update user on status
		printf("Now permuting %s\n", line);

		// clear newline character if it exists
		if( (c = strchr(line, '\n')) != NULL )
			*(c-1) = '\0';
		
		// Print the permutations of the current input line
		CreatePermutations(line, 0, output_ptr);
	}

	// Update user on status and finish program	
	printf("All words permuted successfully. Closing file.\n");
	fclose(output_ptr);
	fclose(input_ptr);
	return 0;
}


// Basic swap function
// Accepts a string and two indexes, swaps the
// the characters at the positions provided
void ExchangeChars(char str[], int i, int j)
{
	char temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}



void CreatePermutations(char str[], int fixed, FILE *output_file)
{
	int j;

	// Base Case: If all 'fixed' is equal to string length, all positions are
	// fixed. Print permutation.
	if( fixed == strlen( str ) ) {
		fprintf(output_file,"%s\n", str);
	}
	else
	{
		// Place a new characters in spot j
		for( j = fixed; j < strlen( str ); j++ )
		{
			// place next character in spot 'fixed'
			ExchangeChars(str, fixed, j);

			// Print all permutations with the specified starting 
			// positions fixed.
			CreatePermutations(str, fixed+1, output_file);

			// Put the swapped characters back to their original
			// positions.
			ExchangeChars(str, j, fixed);
		}
	}
}

void die( char *error_message )
{
	printf("**%s\n", error_message);
	exit(1);
}
