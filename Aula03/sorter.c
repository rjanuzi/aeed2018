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
	int i, j, k;
	
	for(i = 1; i < len; i++)
	{
		for(j = i-1, k = i; j >= 0; j--, k--)
		{
			//Se no subvetor ordenado de 0 a j nao tem elementos maiores que k, k estah no lugar correto.
			if(k == 0 || array[k] > array[j])
				break;
			else
				sorter_swap(&array[k], &array[j]); //Troca com o anterior até encontrar a posição final.
		}
	}
}
