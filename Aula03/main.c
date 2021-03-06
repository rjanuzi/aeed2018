#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrays.h"
#include "sorter.h"
#include "timer.h"
#include "csv.h"
#include "tester.h"

#define _10_1 10
#define _10_2 100
#define _10_3 1000
#define _10_4 10000
#define _10_5 100000
#define _10_6 1000000
#define _10_7 10000000
#define _10_8 100000000

#define RANDOM_STR	" (RANDOM)"
#define ASC_STR 	" (ASC)"
#define DESC_STR 	" (DESC)"

void runExecTest(void (*algorithm)(int*,int), char* algorithmName, FILE* openedFile);
unsigned long long avg(unsigned long long* times);

int main( void )
{
	FILE* openedFile;

//	tester_checkSortAlgorithm(&sorter_heapSort);

	openedFile = csv_create("times.csv");
	runExecTest(&sorter_selectionSort, "Selection Sort", openedFile);
	runExecTest(&sorter_insertionSort, "Insertion Sort", openedFile);
	runExecTest(&sorter_bubbleSort, "Bubble Sort", openedFile);
	runExecTest(&sorter_shellSort, "Shell Sort", openedFile);
	runExecTest(&sorter_quickSortCaller, "Quick Sort", openedFile);
	runExecTest(&sorter_heapSort, "Heap Sort", openedFile);

	fclose(openedFile);

	return 0;
}

void runExecTest(void (*algorithm)(int*,int), char* algorithmName, FILE* openedFile)
{
	int sizes[8] = {_10_1, _10_2, _10_3, _10_4, _10_5, _10_6, _10_7, _10_8};
	void* ptr;
	csvLine_t lineTemp;
	int* array;
	int i, j;
	char* relativeName;
	unsigned long long times[5];

	if(openedFile == NULL)
	{
		printf("[ERROR]: main.runExecTest() - file == null for %s", algorithmName);
		return;
	}

	//Exec with Random array
	relativeName = calloc(strlen(algorithmName) + strlen(RANDOM_STR), 1);
	strcpy(relativeName, algorithmName);
	strcat(relativeName, RANDOM_STR);

	printf("\nTesting %s...\n", relativeName);

	lineTemp.algorithm = relativeName;
	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 5; i++, ptr += sizeof(unsigned long long) )
	{
		for(j = 0; j < 5; j++)
		{
			array = arrays_genRandomArray(sizes[i]);
			timer_start();
			algorithm(array, sizes[i]);
			times[j] = timer_uStop();
			free(array);
		}

		*((unsigned long long*)ptr) = avg(times);
	}

	printf("Done.\n");

	//Save results
	csv_appendLine(openedFile, lineTemp);

	//Exec with ASC sorted array
	relativeName = calloc(strlen(algorithmName) + strlen(ASC_STR), 1);
	strcpy(relativeName, algorithmName);
	strcat(relativeName, ASC_STR);

	printf("\nTesting %s...\n", relativeName);

	lineTemp.algorithm = relativeName;
	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 5; i++, ptr += sizeof(unsigned long long) )
	{
		for(j = 0; j < 5; j++)
		{
			array = arrays_genSortedAscArray(sizes[i]);
			timer_start();
			algorithm(array, sizes[i]);
			times[j] = timer_uStop();
			free(array);
		}

		*((unsigned long long*)ptr) = avg(times);
	}

	printf("Done.\n");

	//Save results
	csv_appendLine(openedFile, lineTemp);

	//Exec with DESC sorted array
	relativeName = calloc(strlen(algorithmName) + strlen(DESC_STR), 1);
	strcpy(relativeName, algorithmName);
	strcat(relativeName, DESC_STR);

	printf("\nTesting %s...\n", relativeName);

	lineTemp.algorithm = relativeName;
	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 5; i++, ptr += sizeof(unsigned long long) )
	{
		for(j = 0; j < 5; j++)
		{
			array = arrays_genSortedDescArray(sizes[i]);
			timer_start();
			algorithm(array, sizes[i]);
			times[j] = timer_uStop();
			free(array);
		}

		*((unsigned long long*)ptr) = avg(times);
	}

	printf("Done.\n");

	//Save results
	csv_appendLine(openedFile, lineTemp);
}

unsigned long long avg(unsigned long long* times)
{
	unsigned long long result;

	result = (times[0]+times[1]+times[2]+times[3]+times[4])/5;

//	printf("\n%lld, %lld, %lld, %lld, %lld -> %lld\n", times[0],times[1],times[2],times[3],times[4], result);

	return result;
}

