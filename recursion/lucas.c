#include <stdio.h>

int lucas(n)
{
	// caluculate lucas number recursively
	if( n == 1 )
		return 1;
	else if( n == 2 )
		return 3;
	else
		return lucas( n - 1) + lucas( n - 2 );
}

int main()
{
	int i;
	for( i = 1; i <= 10; i++ )
	{
		printf("Lucas(%d) ==> %d\n", i, lucas(i));
	}
	return 0;
}
