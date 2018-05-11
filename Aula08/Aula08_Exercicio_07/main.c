#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "arrays.h"
#include "timer.h"
#include "csv.h"

#define N 10000

void testArray(FILE* outputFile);
void testBinaryArray(FILE* outputFile);
void testBinaryTree(FILE* outputFile);
void testAvlTree(FILE* outputFile);

int main( void )
{
	FILE* openedFile;

	openedFile = csv_create("times.csv");

	testArray(openedFile);
	testBinaryArray(openedFile);
	testBinaryTree(openedFile);
	testAvlTree(openedFile);

	printf("\nEnd\n");

	fclose(openedFile);

	return 0;
}

void testArray(FILE* outputFile)
{
	unsigned long long elapsedTime;
	csvLine_t line;
	int* array;
	int bigger = INT_MAX, lower = INT_MIN, i;

	//Test Insertion
	timer_start();
	array = arrays_genRandomArray(N);
	elapsedTime = timer_uStop();

	line.testName = "Array\0";
	line.timeInsertion = elapsedTime;

	//Test Buscar o maior
	timer_start();

	for(i = 0; i < N; i++)
		if(bigger < array[i])
			bigger = array[i];

	elapsedTime = timer_uStop();

	line.timeSearchBigger = elapsedTime;

	//Test Buscar o menor
	timer_start();

	for(i = 0; i < N; i++)
		if(lower > array[i])
			lower = array[i];

	elapsedTime = timer_uStop();

	line.timeSearchLower = elapsedTime;

	csv_appendLine(outputFile, line);
}

void testBinaryArray(FILE* outputFile)
{
	//TODO
}

void testBinaryTree(FILE* outputFile)
{
	//TODO
}

void testAvlTree(FILE* outputFile)
{
	//TODO
}
