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
		printf("\nRandom - Asc ok\n");
	else
		printf("\nRandom - Asc ko\n");
	free(array);

	array = arrays_genRandomArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, true))
		printf("\nRandom - Desc ok\n");
	else
		printf("\nRandom - Desc ko\n");
	free(array);

	//Sorted array asc
	array = arrays_genSortedAscArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, false))
		printf("\nAsc - Asc ok\n");
	else
		printf("\nAsc - Asc ko\n");
	free(array);

	array = arrays_genSortedAscArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, true))
		printf("\nAsc - Desc ok\n");
	else
		printf("\nAsc - Desc ko\n");
	free(array);

	//Sorted array desc
	array = arrays_genSortedDescArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, false))
		printf("\nDesc - Asc ok\n");
	else
		printf("\nDesc - Asc ko\n");
	free(array);

	array = arrays_genSortedDescArray(TESTER_ARRAY_LEN);
	algorithm(array, TESTER_ARRAY_LEN); //Sorting
	if(tester_isSorted(array, TESTER_ARRAY_LEN, true))
		printf("\nDesc - Desc ok\n");
	else
		printf("\nDesc - Desc ko\n");
	free(array);
}
