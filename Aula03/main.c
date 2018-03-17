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

int main( void )
{

//	tester_checkSortAlgorithm(&sorter_selectionSort);

	runExecTest(&sorter_selectionSort, "selectionSort", csv_create("times.csv"));

	return 0;
}

void runExecTest(void (*algorithm)(int*,int), char* algorithmName, FILE* openedFile)
{
	int sizes[8] = {_10_1, _10_2, _10_3, _10_4, _10_5, _10_6, _10_7, _10_8};
	void* ptr;
	csvLine_t lineTemp;
	int* array;
	int i;
	char* relativeName;

	if(openedFile == NULL)
	{
		printf("[ERROR]: main.runExecTest() - file == null for %s", algorithmName);
		return;
	}

	//Exec with Random array
	relativeName = calloc(strlen(algorithmName) + strlen(RANDOM_STR), 1);
	strcpy(relativeName, algorithmName);
	strcat(relativeName, RANDOM_STR);

	lineTemp.algorithm = relativeName;
	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 8; i++, ptr += sizeof(unsigned long long) )
	{
		timer_start();
		array = arrays_genRandomArray(sizes[i]);
		*((unsigned long long*)ptr) = timer_uStop();
		free(array);
	}

	//Save results
	csv_appendLine(openedFile, lineTemp);

	//Exec with ASC sorted array
	relativeName = calloc(strlen(algorithmName) + strlen(ASC_STR), 1);
	strcpy(relativeName, algorithmName);
	strcat(relativeName, ASC_STR);

	lineTemp.algorithm = relativeName;
	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 8; i++, ptr += sizeof(unsigned long long) )
	{
		timer_start();
		array = arrays_genSortedAscArray(sizes[i]);
		*((unsigned long long*)ptr) = timer_uStop();
		free(array);
	}

	//Save results
	csv_appendLine(openedFile, lineTemp);

	//Exec with DESC sorted array
	relativeName = calloc(strlen(algorithmName) + strlen(DESC_STR), 1);
	strcpy(relativeName, algorithmName);
	strcat(relativeName, DESC_STR);

	lineTemp.algorithm = relativeName;
	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 8; i++, ptr += sizeof(unsigned long long) )
	{
		timer_start();
		array = arrays_genSortedDescArray(sizes[i]);
		*((unsigned long long*)ptr) = timer_uStop();
		free(array);
	}

	//Save results
	csv_appendLine(openedFile, lineTemp);

	fclose(openedFile);
}

