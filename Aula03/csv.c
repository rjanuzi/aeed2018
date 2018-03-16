#include "csv.h"

FILE* csv_create(char* filePath)
{
	FILE* file;

	file = fopen(filePath, "w+");

	if(file == NULL)
		printf("\n[ERROR]: csv_openFile() - Opening file failure.\n");
	else
		fprintf(file, "Algorithm;10^1;10^2;10^3;10^4;10^5;10^6;10^7;10^8\n");

	return file;
}

void csv_appendLine(FILE* file, csvLine_t line)
{
	if(file == NULL)
		printf("\n[ERROR]: csv_appendToFile() - File is NULL\n");

	fprintf(file, "%s;%lld;%lld;%lld;%lld;", line.algorithm, line._10_1_time, line._10_2_time, line._10_3_time, line._10_4_time);
	fprintf(file, "%lld;%lld;%lld;%lld;\n", line._10_5_time, line._10_6_time, line._10_7_time, line._10_8_time);
}

void csv_printLine(csvLine_t line)
{
	printf("\n%s;%lld;%lld;%lld;%lld;", line.algorithm, line._10_1_time, line._10_2_time, line._10_3_time, line._10_4_time);
	printf("%lld;%lld;%lld;%lld;\n", line._10_5_time, line._10_6_time, line._10_7_time, line._10_8_time);
}
