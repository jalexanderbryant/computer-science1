#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 35

void print_duplicate( char *listOne[], char *listTwo[], int lenOne, int lenTwo);
int main(int argc, char *argv[])
{
	char *setOne[] = {
		"Adams",
		"Bell",
		"Davis",
		"Harding",
		"Jenkins",
		"Lincoln",
		"Simpson",
		"Zoeller" };
	char *setTwo[] = {
		"Boston",
		"Davis",
		"Duncan",
		"Francis",
		"Gamble",
		"Harding",
		"Mason",
		"Simpson"};

	int len1 = sizeof( setOne ) / sizeof(setOne[0]);
	printf("%d\n", len1);

	print_duplicate( setOne, setTwo, len1, len1 );
	return 0;
}

void print_duplicate( char *listOne[], char *listTwo[], int lenOne, int lenTwo)
{
	int mark1, mark2;
	mark1 = mark2 = 0;
	
	while( (mark1 < lenOne) &&  (mark2 < lenOne) )
	{
		int result = strcmp( listOne[mark1], listTwo[mark2] );
		
		if( result < 0 )
			mark1++;
		else if( result > 0 )
			mark2++;
		else {
			printf("The name %s appears in both lists.\n",
				listOne[mark1]);
			mark1++;
			mark2++;
		}
	}
}

