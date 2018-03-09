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

	for(int loop = 0; loop < loopCount; loop++)
	{
		//TODO
		changesCount[0];
	} 

	return 0;
}
