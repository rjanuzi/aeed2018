#include <stdio.h>

typedef struct stack_s {
	int top;
	char stack[300]; // Input has bases in [1,300]
} stack_t;

int main( void )
{
	stack_t stack;
	char newChar;
	int connectionsTemp;

	stack.top = -1; //Init stack
	connectionsTemp = 0;

	while( 1 )
	{
		if(scanf("%c", &newChar) == EOF) //Read char and check for the test end
		{
			printf("%d\n", connectionsTemp); //Print result for the last line and end
			break;

		} else
			if(newChar == '\n') //Check for the next test
			{
				printf("%d\n", connectionsTemp); //Print result for the line
				stack.top = -1; //Reinit stack;
				connectionsTemp = 0; //Reset the connections count

			} else //Check if the new readed base makes a connection with the stack's top
			{
				if( stack.top >= 0 ) //If the stack is not empty check the bases for connectivity
				{
					//Check for a valid combination between the new char and the stack's top

					if( ( ('B' == newChar) && ('S' == stack.stack[stack.top]) ) ||
							( ('S' == newChar) && ('B' == stack.stack[stack.top]) ) ||
							( ('C' == newChar) && ('F' == stack.stack[stack.top]) ) ||
							( ('F' == newChar) && ('C' == stack.stack[stack.top]) ))
					{
						stack.top--;			//Pop the stack
						connectionsTemp++;		//Inc the connections made count
					}
					else
						stack.stack[++stack.top] = newChar; //Push the new char on stack
				}
				else
					stack.stack[++stack.top] = newChar; //Push the new char on stack

			}
	}

	return 0;
}

