#include <stdio.h>

int main()
{
	int i  = 0;
	int j = 32;
	while( j > 0 )
	{
		printf("%d\n", j%2);
		j = j/2;
	}
	return 0;
}
