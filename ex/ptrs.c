#include <stdio.h>

int main() 
{
	double values[10];
	double *p;
	p = &values[9];

	while( p >= &values[0] )
	{
		scanf("%lf", p);
		p = p-1;
	}

	int i = 0;
	for( ; i < 10; i++)
	{
		printf(" #%p -> values[%d] -> %lf\n",
			&values[i],
			i,
			values[i] );
	}

	return 0;
}
