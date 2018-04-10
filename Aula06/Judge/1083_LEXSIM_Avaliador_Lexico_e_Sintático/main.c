#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

//Get the top char, without remove-it
char getTop(stack_t** stack)
{
	if(*stack == NULL)
		return '\0';
	return (*stack)->val;
}

bool isOperando(char val)
{
	if(val >= 'a' && val <= 'z')
		return true;

	if(val >= 'A' && val <= 'Z')
		return true;

	if(val >= '0' && val <= '9')
		return true;

	return false;
}

int getPrio(char val)
{
	switch(val)
	{
	case '^':
		return 6;

	case '*':
	case '/':
		return 5;

	case '+':
	case '-':
		return 4;

	case '>':
	case '<':
	case '=':
	case '#':
		return 3;

	case '.':
		return 2;

	case '|':
		return 1;

	default:
		return 0;
	}
}

bool hasGreaterPrior(char a, char b)
{
	if(getPrio(a) > getPrio(b))
		return true;
	return false;
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
	int i;

	//To Test
	char input[] = {'a', '+', 'b', '*', 'c', '^', 'd', '-', 'e'};
	int len;

	printf("\n");
	len = strlen(input);
	for(i = 0; i < len; i++)
	{
		//If is operand, print it
		if(isOperando(input[i]))
		{
			printf("%c", input[i]);
			continue;
		}

		//TODO - Check if is parenthesis

		//If is operator AND
		//(the stack is empty OR the new input has greater priority than stack's top)
		//Push it
		if(stack == NULL || hasGreaterPrior(input[i], getTop(&stack)))
			push(&stack, input[i]);
		else { //If the new input has lower priority than stack's top, print it
			printf("%c", input[i]);
			continue;
		}
	}

	//Pop and print the lasting operators
	while(stack != NULL)
	{
		printf("%c", pop(&stack));
	}

	return 0;
}
