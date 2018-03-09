#include <stdio.h>
#include <stdlib.h>

int main( void )
{

	int itensCount, loopCount;
	int* changesCount;
	int* result;

	itensCount = 3;
	loopCount = 1;
	result = malloc(sizeof(int) * itensCount);
	changesCount = malloc(sizeof(int) * loopCount);
	
	changesCount[0] = 1;

	return 0;
}
