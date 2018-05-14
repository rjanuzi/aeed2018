#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "arrays.h"
#include "timer.h"
#include "csv.h"
#include "trees.h"

#define N 10000
//#define N 10000000

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
	int bigger = INT_MIN, lower = INT_MAX, i;

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

	printf("Array: Bigger = %d, Lower = %d\n", bigger, lower);

	csv_appendLine(outputFile, line);

	free(array);
}

void testBinaryArray(FILE* outputFile)
{
	unsigned long long elapsedTime;
	csvLine_t line;
	int* array;
	int bigger = INT_MAX, lower = INT_MIN, i;

	//Test Insertion
	timer_start();
	array = arrays_genRandomSortedArray(N);
	elapsedTime = timer_uStop();

	line.testName = "Binary Array\0";
	line.timeInsertion = elapsedTime;

	//Test Buscar o maior
	timer_start();
	bigger = array[N-1];
	elapsedTime = timer_uStop();

	line.timeSearchBigger = elapsedTime;

	//Test Buscar o menor
	timer_start();
	lower = array[0];
	elapsedTime = timer_uStop();

	line.timeSearchLower = elapsedTime;

	printf("Binary Array: Bigger = %d, Lower = %d\n", bigger, lower);

	csv_appendLine(outputFile, line);

	free(array);
}

void testBinaryTree(FILE* outputFile)
{
	unsigned long long elapsedTime;
	csvLine_t line;
	binTree_t* root;
	binTree_t* nodeTemp;
	int bigger = INT_MAX, lower = INT_MIN;

	//Test Insertion
	timer_start();
	root = trees_genRandomBinTree(N);
	elapsedTime = timer_uStop();

	line.testName = "Binary Tree\0";
	line.timeInsertion = elapsedTime;

	//Test Buscar o maior
	timer_start();

	//The bigger is the most right leaf
	nodeTemp = root;
	while(nodeTemp->right != NULL)
		nodeTemp = nodeTemp->right;

	bigger = nodeTemp->val;

	elapsedTime = timer_uStop();

	line.timeSearchBigger = elapsedTime;

	//Test Buscar o menor
	timer_start();

	//The lower is the most left leaf
	nodeTemp = root;
	while(nodeTemp->left != NULL)
		nodeTemp = nodeTemp->left;

	lower = nodeTemp->val;

	elapsedTime = timer_uStop();

	line.timeSearchLower = elapsedTime;

	printf("Binary Tree: Bigger = %d, Lower = %d\n", bigger, lower);

	csv_appendLine(outputFile, line);

	trees_freeBinTree(root);
}

void testAvlTree(FILE* outputFile)
{
	//TODO
}
