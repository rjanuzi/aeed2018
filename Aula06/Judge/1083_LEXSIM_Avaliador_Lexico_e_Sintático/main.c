#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

typedef struct stack_s {
	char val;
	struct stack_s* below;
} stack_t;

void push(stack_t** stack, char val)
{
	stack_t* newNode;

	if(DEBUG)
		printf("\nPushing %c\n", val);

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
	{
		if(DEBUG)
			printf("\nPoping a empty stack\n");

		return '\0';
	}

	nodeToRemove = *stack;
	*stack = (*stack)->below;

	result = nodeToRemove->val;

	if(DEBUG)
		printf("\nPoping %c\n", result);

	free(nodeToRemove);

	return result;
}

//Get the top char, without remove-it
char getTop(stack_t** stack)
{
	if(*stack == NULL)
	{
		if(DEBUG)
			printf("\nGetiing top from empty stack\n");

		return '\0';
	}

	if(DEBUG)
		printf("\nGetting top %c\n", (*stack)->val);

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

bool isOperator(char val)
{
	if(val == '^' ||
			val == '*' || val == '/' ||
			val == '+' || val == '-' ||
			val == '>' || val == '<' || val == '=' || val == '#' ||
			val == '.' ||
			val == '|')
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
		printf("\nNode %d: %c", i++, currentNode->val);
}

int main( void )
{
	stack_t* stack = NULL;
	int i = -1;
	char tempChar, tempChar2;

	do {

		scanf("%c", &tempChar);

		//If is operand, print it
		if(isOperando(tempChar))
		{
			printf("%c", tempChar);
			continue;
		}

		if(tempChar == '(')
		{
			push(&stack, tempChar);
			continue;
		}

		if(tempChar == ')' || tempChar == '!')
		{
			while( stack != NULL && (tempChar2 = pop(&stack)) != '(' )
				printf("%c", tempChar2);

			continue;
		}

		if(isOperator(tempChar))
		{
			while(true)
			{
				//If is operator AND (the stack is empty OR the new input has greater priority than stack's top)
				//Push it, and goes to next char
				if(stack == NULL || hasGreaterPrior(tempChar, getTop(&stack)))
				{
					push(&stack, tempChar);
					break;
				}
				else //The stack's top has minor or equal priority than new input, pop and print it. Then goes to next stack char
					printf("%c", pop(&stack));
			}
		}

	} while(tempChar != '!');

	if(stack == NULL) {
		//TODO - print posfixed
	}
	else
		if(isOperator(getTop(&stack)))
			printf("Syntax Error!");
		else
			printf("Lexical Error!");

	printStack(&stack);

	return 0;
}
