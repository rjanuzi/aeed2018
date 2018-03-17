/**
*	@file tester.h
*
*	@author Rafael B. Januzi
*	@date 17/03/2018
*
*	@brief This module contains some utility function to check if a array is sorted.
*/

#ifndef _TESTER_H
#define _TESTER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "arrays.h"

#define TESTER_ARRAY_LEN 10000

bool tester_isSorted(int* array, int len, bool desc);
bool tester_checkSortAlgorithm(void (*algorithm)(int*,int));

#endif /* _TESTER_H */


