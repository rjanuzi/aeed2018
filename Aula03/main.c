#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#include "sorter.h"
#include "timer.h"
#include "csv.h"

#define _10_1 10
#define _10_2 100
#define _10_3 1000
#define _10_4 10000
#define _10_5 100000
#define _10_6 1000000
#define _10_7 10000000
#define _10_8 100000000

int main( void )
{
	int* array;
	csvLine_t lineTemp;
	FILE* timesFile;
	int i;
	int sizes[8] = {_10_1, _10_2, _10_3, _10_4, _10_5, _10_6, _10_7, _10_8};
	void* ptr;

	lineTemp.algorithm = "genRandomArray()";


	for(i = 0, ptr = (void*) &lineTemp._10_1_time; i < 8; i++, ptr += sizeof(unsigned long long) )
	{
		timer_start();
		array = arrays_genRandomArray(sizes[i]);
		*((unsigned long long*)ptr) = timer_uStop();
		free(array);
	}

	//Save file
	timesFile = csv_create("times.csv");
	csv_appendLine(timesFile, lineTemp);
	fclose(timesFile);

	return 0;
}

