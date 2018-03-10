#include <stdio.h>
#include <stdlib.h>

#define MAX_LOOPS 100000

int main( void )
{
	int itensCount, loopCount, totalSwapsExpected = 0, temp;
	int* swapsDoneCount;
	int* result;

	//Le primeira linha
	itensCount = 6;
	loopCount = 5;
	result = malloc(sizeof(int) * itensCount);
	
	//Le segunda linha
	swapsDoneCount = malloc(sizeof(int) * loopCount);
	swapsDoneCount[0] = 2;
	swapsDoneCount[1] = 2;
	swapsDoneCount[2] = 2;
	swapsDoneCount[3] = 2;
	swapsDoneCount[4] = 1;
	
	//Coloca itens ordenados no array result
	for(int i = 0; i < itensCount; i++)
		result[i] = (i+1);

	//Calcula quantos swapsDones devem acontencer
	for(int loop = 0; loop < loopCount; loop++)
		totalSwapsExpected += swapsDoneCount[loop];
	
	//Do final do array para o inicio, realiza trocas 
	//quando o elemento anterior for menor
	for(int swapsDone = 0, loopsMaxCount = 0; swapsDone < totalSwapsExpected && loopsMaxCount < MAX_LOOPS; loopsMaxCount++)
	{
		for(int i = (itensCount-1); i > 0 && swapsDone < totalSwapsExpected; i--)
		{
			if( result[i-1] < result[i] )
			{
				//swapsDone
				temp = result[i-1];
				result[i-1] = result[i];
				result[i] = temp;
				
				swapsDone++;
			}
			else
				continue; //Deixa esse elemento pra la e vai atras do proximo.
		}
	}
	
	for(int i = 0; i < itensCount; i++)
		printf("%d ", result[i]);

	return 0;
}
