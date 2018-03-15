#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#include "sorter.h"
#include "timer.h"

int main( void )
{
	int* array;

	timer_start();

	array = arrays_genRandomArray(100000);

	printf("%lld us\n", timer_uStop());

	free(array);

	return 0;
}

