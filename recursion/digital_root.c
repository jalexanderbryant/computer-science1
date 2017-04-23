#include <stdio.h>

int DigitSum( int n )
{
	if( n > 0 )
		return n%10 + DigitSum(n/10);
	return 0;
}

int DigitalRoot( int n)
{
	int sumd = DigitSum(n);
	if( sumd > 9)
		return DigitalRoot(sumd);
	return sumd;
}


int main( int argc, char *argv[] )
{
	int val;
	
	start:
	printf("Enter a value: ");
	scanf("%d", &val);
	
	printf("%d\n", val);
	if( val == 0 ) goto end;

	printf("Digital root of %d is %d\n", val, DigitalRoot(val) );
	goto start;

	end:
	return 0;
}
