/**
*	@file csv.h
*
*	@author Rafael B. Januzi
*	@date 15/03/2018
*
*	@brief This module contains some utility csv functions
*/

#ifndef _CSV_H
#define _CSV_H

#include <stdlib.h>
#include <stdio.h>

typedef struct csvLine_s
{
	char* testName;
	unsigned long long timeInsertion;
	unsigned long long timeSearchBigger;
	unsigned long long timeSearchLower;
} csvLine_t;

FILE* csv_create(char* filePath);
void csv_appendLine(FILE* file, csvLine_t line);
void csv_printLine(csvLine_t line);

#endif /* _CSV_H */


