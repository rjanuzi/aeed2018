#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_BASES 300
#define VALID_COMBINATION_COUNT 4

const char* validCombination[] = {"BS", "SB", "CF", "FC"};

typedef struct stack_s {
	int top;
	char stack[MAX_BASES]; // Input has bases in [1,300]
} stack_t;

void init(stack_t* stack);
bool push(stack_t* stack, char base);
char pop(stack_t* stack);
char getTop(stack_t* stack);
void printStack(stack_t* stack);

int main( void )
{
	stack_t stack;
	char pairTemp[2];
	char newChar;
	int connectionsTemp, i;
	bool connectionMade;

	init(&stack);
	connectionsTemp = 0;

	while( true )
	{
		scanf("%c", &newChar); //Read char

		if(newChar == EOF) //Check for the test end
		{
			printf("%d\n", connectionsTemp); //Print result for the last line and end
			break;

		} else
			if(newChar == '\n') //Check for the next test
			{
				printf("%d\n", connectionsTemp); //Print result for the line
				init(&stack); //Reinit stack;
				connectionsTemp = 0; //Reset the connections count

			} else //Check if the new readed base makes a connection with the stack's top
			{
				connectionMade = false; //Assumes thats no connection will be made.

				if( (pairTemp[0] = getTop(&stack)) != -1 ) //If the stack is not empty check the bases for connectivity
				{
					pairTemp[1] = newChar; //Now the pairTemp has the stack's top and the new char

					//Check for a valid combination between the stack's top and the new char
					for(i = 0; i < VALID_COMBINATION_COUNT; i++)
						if(strcmp(validCombination[i], pairTemp) == 0)
						{
							connectionMade = true; //Combination finded
							break; //Skip remaining validations
						}
				}

				if(connectionMade)
				{
					pop(&stack); //Pop the stack
					connectionsTemp++; //Inc the connections made count
				}
				else
					push(&stack, newChar); //Push the new char on stack
			}
	}

	return 0;
}

void init(stack_t* stack)
{
	(*stack).top = -1;
	memset((void*)&(*stack).stack, '\0', MAX_BASES);
}

bool push(stack_t* stack, char base)
{
	if((*stack).top >= MAX_BASES)
	{
		printf("\n[ERROR]: Stack exploded!");
		return false;
	}

	(*stack).stack[++(*stack).top] = base;

	return true;
}

char pop(stack_t* stack)
{
	char element;

	if((*stack).top < 0)
		return -1;

	element = (*stack).stack[(*stack).top];
	(*stack).stack[(*stack).top--] = '\0';

	return element;
}

/**
 * Get the top element without remove it
 */
char getTop(stack_t* stack)
{
	if((*stack).top < 0)
		return -1;

	return (*stack).stack[(*stack).top];
}

void printStack(stack_t* stack)
{
	int i;

	printf("\nStack:\n\tTop: %d\nStack: ", (*stack).top);

	for(i = 0; i < MAX_BASES; i++)
		printf(" %c ", (*stack).stack[i]);
}
