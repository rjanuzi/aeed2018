#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

typedef struct stack_s {
	char val;
	struct stack_s* below;
} stack_t;

typedef struct list_s {
	char val;
	struct list_s* nxt;
} list_t;

void push(stack_t** stack, char val)
{
	stack_t* newNode;

	if(DEBUG)
		printf("\nPushing %c\n", val);

	newNode = calloc(sizeof(stack_t), 1);
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

void add(list_t** list, char val)
{
	list_t* newNode;
	list_t* last;

	newNode = malloc(sizeof(list_t));
	newNode->val = val;
	newNode->nxt = NULL;

	if(*list == NULL)
		*list = newNode;
	else
	{
		last = *list;
		while(last->nxt != NULL)
			last = last->nxt;

		last->nxt = newNode;
	}
}

char removeFirst(list_t** list)
{
	list_t* nodeToRemove;
	char result;

	if(*list == NULL)
		return '\0';

	nodeToRemove = *list;
	*list = (*list)->nxt;

	result = nodeToRemove->val;

	free(nodeToRemove);

	return result;
}

void printRemoveAll(list_t** list)
{
	while(*list != NULL)
		printf("%c", removeFirst(list));
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
	list_t* outBuffer = NULL;
	stack_t* stack = NULL;
	char newChar, tempChar;

	while(true) {

		//Program end - Print result for the last input and end program
		if(scanf("%c", &newChar) == EOF)
		{
			if(stack == NULL)
				printRemoveAll(&outBuffer);
			else
				printf("Syntax Error!\n");

			break;
		}

		//If is operand, print it
		if(isOperando(newChar))
		{
			add(&outBuffer, newChar);
			continue;
		}

		if(newChar == '(')
		{
			push(&stack, newChar);
			continue;
		}

		if(newChar == ')')
		{
			while( stack != NULL && (tempChar = pop(&stack)) != '(' )
				add(&outBuffer, tempChar);
			continue;
		}

		if(isOperator(newChar))
		{
			while(true)
			{
				//If is operator AND (the stack is empty OR the new input has greater priority than stack's top)
				//Push it, and goes to next char
				if(stack == NULL || hasGreaterPrior(newChar, getTop(&stack)))
				{
					push(&stack, newChar);
					break;
				}
				else //The stack's top has minor or equal priority than new input, pop and print it. Then goes to next stack char
					add(&outBuffer, pop(&stack));
			}

			continue;
		}

		//Line end - Print result for the last line and reinit stack and flags
		if(newChar == '\n')
		{
			while( stack != NULL && isOperator(getTop(&stack)) )
				add(&outBuffer, pop(&stack));

			if(stack == NULL) {
				printRemoveAll(&outBuffer);
				printf("\n");
			}
			else
				printf("Syntax Error!\n");

			//Reinit stack
			while(stack != NULL)
				pop(&stack);

			continue;
		}

		//If reach this point the char is not know or is the termination char

		//Lexical Error finded - print message and reinit the stack
		printf("Lexical Error!\n");

		//Reinit stack
		while(stack != NULL)
			pop(&stack);
	}

	return 0;
}
