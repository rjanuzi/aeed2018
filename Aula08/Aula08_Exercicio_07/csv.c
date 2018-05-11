#include "csv.h"

FILE* csv_create(char* filePath)
{
	FILE* file;

	file = fopen(filePath, "w+");

	if(file == NULL)
		printf("\n[ERROR]: csv_openFile() - Opening file failure.\n");
	else
		fprintf(file, "Test Name;Time to Insert;Time to Search Bigger;Time to Search Lower\n");

	return file;
}

void csv_appendLine(FILE* file, csvLine_t line)
{
	if(file == NULL)
		printf("\n[ERROR]: csv_appendToFile() - File is NULL\n");

	fprintf(file, "%s;%lld;%lld;%lld\n", line.testName, line.timeInsertion, line.timeSearchBigger, line.timeSearchLower);
}

void csv_printLine(csvLine_t line)
{
	printf("%s;%lld;%lld;%lld\n", line.testName, line.timeInsertion, line.timeSearchBigger, line.timeSearchLower);
}
