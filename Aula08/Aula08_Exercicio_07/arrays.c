#include "arrays.h"

#define MAX_RAND 1000000

int* arrays_allocArray(int len)
{
	return malloc(sizeof(int) * len);
}

int* arrays_genRandomArray(int len)
{
	int* array;
	int i;

	srand((unsigned) time(NULL));

	array = arrays_allocArray(len);

	for(i = 0; i < len; i++)
		array[i] = (rand() % MAX_RAND);

	return array;
}

int* arrays_genRandomSortedArray(int len)
{
	int* array;
	int i, j, k, newVal;

	srand((unsigned) time(NULL));

	array = arrays_allocArray(len);

	//Shold insert sorted
	for(i = 0; i < len; i++) {
		newVal = (rand() % MAX_RAND);

		for(j = 0; j < i && newVal > array[j]; j++)
			continue;

		if(j == i) //The new element is grater than any other in the array
			array[i] = newVal;
		else { //The new element goes before some elements in the array, so at least one element need to be shifted to right

			//Shift the elements from position j right
			for(k = i; k > j; k--)
				array[k] = array[k-1];

			array[j] = newVal;
		}
	}

	return array;
}

void arrays_print(int* array, int len)
{
	int i;

	printf("\nArray:");
	for(i = 0; i < len; i++)
		printf(" %d ", array[i]);
	printf("\n");
}
