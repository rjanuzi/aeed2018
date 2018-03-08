#include <stdio.h>
#include <stdlib.h>

typedef struct aluno_s {
    int pInicial;
    int nota;
} aluno_t;

void sort(aluno_t** alunos, int len)
{
	int i, j, indexMaior;
	aluno_t alunoTemp;
	
	if(len <= 1)
		return;
	
	for(i = 0; i < len; i++)
	{
		indexMaior = i;

		//Procura o index de um elemento maior que o maior.
		for(j = i+1; j < len; j++)
			if( (*alunos)[indexMaior].nota < (*alunos)[j].nota )
				indexMaior = j;
		
		//Troca se encontrou um elemento maior que o inicial
		if(indexMaior != i)
		{
			alunoTemp = (*alunos)[indexMaior];
			(*alunos)[indexMaior] = (*alunos)[i];
			(*alunos)[i] = alunoTemp;
		}
	}
}

void printAluno(aluno_t alunoToPrint)
{
	printf("\nAluno:\n\tpInicial: %d\n\tnota: %d", alunoToPrint.pInicial, alunoToPrint.nota);
}

int main() {
    
    int i, j, testsCount, alunosCount;
    aluno_t* alunos;
	int* results;
	
	//Lendo numero de testes
    scanf("%d", &testsCount);

	//Instancia o array de resultados
	results = malloc(sizeof(int) * testsCount);
	
	//Para cada caso de teste
	for(i = 0; i < testsCount; i++)
	{
		//Ler o numero de alunos
		scanf("%d", &alunosCount);

		//Instancia array para os alunos
		alunos = malloc(sizeof(aluno_t) * alunosCount);
		
		//Le as notas dos alunos
		for(j = 0; j < alunosCount; j++)
		{
			alunos[j].pInicial = j;
			scanf("%d", &alunos[j].nota);
		}
		
		sort(&alunos, alunosCount);
		
		//Conta quantos nao trocaram de posicao e coloca no results
		results[i] = 0;
		for(j = 0; j < alunosCount; j++)
			if(alunos[j].pInicial == j)
				results[i]++;
			
		free(alunos);
	}
	
	for(i = 0; i < testsCount; i++)
		printf("%d\n", results[i]);
	
	free(results);
	
    return 0;
}