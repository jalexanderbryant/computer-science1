#include <stdio.h>

int main()
{
	FILE *in = fopen("AssignmentFourInput.txt", "r");
	int test;

	while( fscanf(in, "%d", &test) != EOF )
	{
		printf("%d ", test);
	}


	return 0;
}
