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

void sorter_bubbleSort(int* array, int len)
{
	int i, j;

	int p;

	for(j = len; j > 0; j--)
		for(i = 0; i < (j-1); i++)
			if(array[i] > array[i+1])
				sorter_swap(&array[i], &array[i+1]);
}

//Fonte: https://pt.wikipedia.org/wiki/Shell_sort
void sorter_shellSort(int* array, int len)
{
	int i , j , value;
	int gap = 1;

	while(gap < len) {
		gap = 3*gap+1;
	}

	while ( gap > 1) {
		gap /= 3;

		for(i = gap; i < len; i++) {
			value = array[i];
			j = i;

			while (j >= gap && value < array[j - gap]) {
				array[j] = array [j - gap];
				j = j - gap;
			}

			array [j] = value;
		}
	}
}

//Font: https://www.geeksforgeeks.org/quick-sort/
int sorter_partition (int* array, int low, int high)
{
	int pivot = array[high];
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			sorter_swap(&array[i], &array[j]);
		}
	}
	sorter_swap(&array[i + 1], &array[high]);
	return (i + 1);
}

//Font: https://www.geeksforgeeks.org/quick-sort/
void sorter_quickSort(int* array, int low, int high)
{
	if (low < high)
	{
		int pi = sorter_partition(array, low, high);

		sorter_quickSort(array, low, pi - 1);
		sorter_quickSort(array, pi + 1, high);
	}
}

//Just a method assignature adjustment.
void sorter_quickSortCaller(int* array, int len)
{
	sorter_quickSort(array, 0, len-1);
}

//Font: https://pt.wikipedia.org/wiki/Heapsort
void sorter_heapSort(int* array, int len)
{
	int i = len / 2, pai, filho, t;

	while(true) {

		if (i > 0) {
			i--;
			t = array[i];
		} else {
			len--;
			if (len == 0) return;
			t = array[len];
			array[len] = array[0];
		}

		pai = i;
		filho = i * 2 + 1;

		while (filho < len) {
			if ((filho + 1 < len)  &&  (array[filho + 1] > array[filho]))
				filho++;
			if (array[filho] > t) {
				array[pai] = array[filho];
				pai = filho;
				filho = pai * 2 + 1;
			} else {
				break;
			}
		}

		array[pai] = t;
	}
}
