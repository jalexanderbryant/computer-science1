// Write a recursive method to determine the number of 1's in the binary 
// representation of a positive integer n.

//Precondition: n > 0

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Doing consecutive divisions...

Get remainder: n % 2
Check if n/2 == 0
	Check if remainder is 1:
		return 1
	Otherwise
		return 0
Otherwise if n/2 != 0
	If remainder is 0:
		return 0 + numOnes( n/2 )
	if remainder is not 0:
		return 1 + numOnes( n/2 )
*/
int numOnes( int n )
{
	int rem = n % 2;
	if( n/2 == 0 ) {
		if( rem == 1 )
			return 1;
		else
			return 0;
	}
	else
	{
		if( rem == 1 )
			return 1 + numOnes( n/2 );
		else
			return 0 + numOnes( n/2 );
	}
}

int numOnes2( int n )
{
	int rem = n % 2;
	if( n/2 == 0 )
		return rem;
	else
		return rem + numOnes( n/2 );
}

int main( int argc, char *argv[] )
{
	int i;

	for(i = 5; i < 40; i+=2 ) {
		printf("%d has %d 1's in it\n", i, numOnes2(i));
	}


	return 0;
}


