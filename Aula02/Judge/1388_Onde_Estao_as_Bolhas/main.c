#include <stdio.h>
#include <stdlib.h>

#define MAX_LOOPS 100000

int main( void )
{
	int itensCount, loopCount, totalSwapsExpected = 0, temp, i, swapsDone, loopsMaxCount;
	int* result;

	while(1)
	{
		//Le primeira linha
		scanf("%d %d", &itensCount, &loopCount);
		
		if(itensCount == 0 || loopCount == 0)
			break;

		result = calloc(sizeof(int) * itensCount, sizeof(int));
		
		//Le segunda linha
		for(i = 0; i < loopCount; i++)
		{
			scanf("%d", &temp);
			totalSwapsExpected += temp;
		}
		
		//Coloca itens ordenados no array result
		for(i = 0; i < itensCount; i++)
			result[i] = (i+1);
		
		//Do final do array para o inicio, realiza trocas 
		//quando o elemento anterior for menor
		for(swapsDone = 0, loopsMaxCount = 0; swapsDone < totalSwapsExpected && loopsMaxCount < MAX_LOOPS; loopsMaxCount++)
		{
			for(i = (itensCount-1); i > 0 && swapsDone < totalSwapsExpected; i--)
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
		
		for(i = 0; i < itensCount; i++)
			printf("%d ", result[i]);
		printf("\n");
		
		free(result);
	}

	return 0;
}
