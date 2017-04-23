#include <stdio.h>

int bin_coeff( int n, int k)
{
	if( (n == k) || (n == 0) )
		return 1;
	else
		return (bin_coeff(n-1, k-1) + bin_coeff(n-1, k));
}

int main()
{
	int n, k;
	for( n = 0, k = 1; n <= 10; n++, k++)
	{
		printf("C(%d, %d) == %d\n", n, k, bin_coeff(n, k));
	}

	return 0;
}
