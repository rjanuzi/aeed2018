#include <stdio.h>
#include <stdlib.h>

typedef struct stack_s {
	char val;
	struct stack_s* below;
} stack_t;

void push(stack_t** stack, char val)
{
	stack_t* newNode;

	newNode = malloc(sizeof(stack_t));
	newNode->val = val;

	if(*stack == NULL)
		newNode->below = NULL;
	else
		newNode->below = *stack;

	*stack = newNode;
}

char pop(stack_t** stack)
{
	stack_t* nodeToRemove;
	char result;

	if(*stack == NULL)
		return '\0';

	nodeToRemove = *stack;
	*stack = (*stack)->below;

	result = nodeToRemove->val;

	free(nodeToRemove);

	return result;
}

void printStack(stack_t** stack)
{
	stack_t* currentNode;
	int i;

	printf("\n\nStack:");

	for(currentNode = (*stack), i = 0; currentNode != NULL; currentNode = currentNode->below)
		printf("\nNode %d: (%c)", i++, currentNode->val);
}

int main( void )
{
	stack_t* stack = NULL;

	//TODO

	return 0;
}

