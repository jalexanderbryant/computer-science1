#include <stdio.h>

void dectobin( int n )
{
	if(n/2 == 0)
		printf("%d", n);
	else
	{
		dectobin( n/2);
		printf("%d", n%2);
	}
}

int main( int argc, char *argv[] )
{
	int i = 0;
	for( i=0; i < 10; i++)
	{
		printf("\t%d in binary is: ",i);
		dectobin(i);
		printf("\n");
	}
	return 0;
}
