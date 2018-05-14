/**
*	@file arrays.h
*
*	@author Rafael B. Januzi
*	@date 14/03/2018
*
*	@brief This module contains some utility array functions
*/

#ifndef _ARRAYS_H
#define _ARRAYS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int* arrays_allocArray(int len);
int* arrays_genRandomArray(int len);
int* arrays_genRandomSortedArray(int len);
void arrays_print(int* array, int len);

#endif /* _ARRAYS_H */


