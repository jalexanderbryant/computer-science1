#include <stdio.h>
#include <stdlib.h>

void tower( int, char,char,char );

int main()
{
	int n = 4;
	printf("The tower of Hanoi involves the moves:\n\n");
	tower(n, 'A', 'B', 'C');
	return 0;
}

void tower( int n, char frompeg, char topeg, char interpeg )
{
	if(n == 1)
	{
		printf("\nMove disk 1 from peg %c to peg %c", frompeg, topeg);
		return;
	}
	// Move top n-1 disks from A to B, using C as intermediate
	tower( n-1, frompeg, interpeg, topeg);
	//move remaining disk from A to C
	printf("\nMove disk %d from peg %c to peg %c", n, frompeg, topeg);
	// Move n-1 disks from B to C using A as intermediate
	tower(n-1, interpeg, topeg, frompeg);
}
