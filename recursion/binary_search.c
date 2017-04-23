#include <stdio.h>
#include <stdlib.h>

int binSearch( int *values, int low, int high, int searchVal )
{
	int mid;
	if( low <= high)
	{
		mid = (low+high)/2;
		if( searchVal < values[mid] )
			return binSearch( values, low, mid-1, searchVal );
		else if ( searchVal > values[mid] )
			return binSearch( values, mid+1, high, searchVal );
		else
			return 1;
	}
	return 0;
}

int main( int argc, char *argv[] )
{
	int *values, key, amt;
	printf("How many values do you need? ");
	// Get the amount of values
	scanf("%d", &amt);

	// Allocate memory for those values
	values = (int *)calloc(amt, sizeof(int));

	int i = 0;
	for( i = 0; i < amt; i++)
	{
		printf("Enter a value: \n");
		scanf("%d", &values[i]); 
	}

	for( i = 0; i < amt; i++ )
		printf("%d ", values[i]);
	printf("\n");
	
	loop:
	printf("Enter a key to search for: ");
	scanf("%d", &key);
	if( key == 0 ) goto end;

	int res = binSearch(values,0, amt-1, key);
	
	if( res == 1 )
		printf("%d was found in the list.\n", key);
	else if( res == 0 )
		printf("%d was not found in the list.\n", key);
	goto loop;
	end:
	printf("End\n");
}
