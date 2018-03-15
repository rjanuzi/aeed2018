#include "arrays.h"

#define MAX_RAND 1000000

int* arrays_allocArray(int len)
{
	return calloc(sizeof(int) * len, sizeof(int));
}

int* arrays_genRandomArray(int len)
{
	static bool srandInitiated = false;
	int* array;
	int i;

	if(!srandInitiated)
	{
		srand((unsigned) time(NULL));
		srandInitiated = true;
	}

	array = arrays_allocArray(len);

	for(i = 0; i < len; i++)
		array[i] = (rand() % MAX_RAND);

	return array;
}
