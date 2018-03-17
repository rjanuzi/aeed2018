#include "sorter.h"

void sorter_swap(int* a, int* b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void sorter_selectionSort(int* array, int len)
{
	int i, j, menor;

	for(i = 0; i < len-1; i++)
	{
		menor = i;
		for(j = i+1; j < len; j++)
			if(array[j] < array[menor])
				menor = j;
		
		if(menor != i)
			sorter_swap(&array[i], &array[menor]);
	}
}

void sorter_insertionSort(int* array, int len)
{
	
}
