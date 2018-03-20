/**
 *	@file sorter.h
 *
 *	@author Rafael B. Januzi
 *	@date 14/03/2018
 *
 *	@brief This module contains some sort algorithms for.
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void sorter_swap(int* a, int* b);

void sorter_selectionSort(int* array, int len);

void sorter_insertionSort(int* array, int len);

void sorter_bubbleSort(int* array, int len);

void sorter_shellSort(int* array, int len);

int sorter_partition (int* array, int low, int high);
void sorter_quickSort(int* array, int low, int high);
void sorter_quickSortCaller(int* array, int len);

void sorter_heapSort(int* array, int len);

#endif /* _SORTER_H */


