#include "tester.h"

bool tester_isSorted(int* array, int len, bool desc)
{
	int i;

	if(desc) /* Desc */
	{
		for(i = 0; i < len-1; i++)
			if(array[i] < array[i+1])
				return false;
	}
	else /* Asc */
	{	
		for(i = 0; i < len-1; i++)
			if(array[i] > array[i+1])
				return false;
	}

	return true;
}

bool tester_checkSortAlgorithm(void (*algorithm)(int*,int))
{
	int* array;

	//Random array
	array = arrays_genRandomArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, false))
		printf("\nRandom ok\n");
	else
		printf("\nRandom ko\n");
	free(array);

	//Sorted array asc
	array = arrays_genSortedAscArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, false))
		printf("\nAsc ok\n");
	else
		printf("\nAsc ko\n");
	free(array);

	//Sorted array desc
	array = arrays_genSortedDescArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, false))
		printf("\nDesc ok\n");
	else
		printf("\nDesc ko\n");
	free(array);
}
