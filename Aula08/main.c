#include <stdio.h>
#include <stdlib.h>

typedef struct tree_s {
	int val;
	struct tree_s* right;
	struct tree_s* left;
	struct tree_s* father;
} tree_t;

typedef struct stack_s {
	int val;
	tree_t* below;
} stack_t;

void add(tree_t** root, int val)
{
	tree_t* newNode;
	tree_t* tempNode;

	newNode = malloc(sizeof(tree_t));

	newNode->val = val;
	newNode->left = NULL;
	newNode->right = NULL;

	if(*root == NULL)
	{
		//		printf("Add root\n");
		newNode->father = NULL;
		*root = newNode;
		return;
	}

	tempNode = *root;

	while(1)
	{
		if(val > tempNode->val) //Goes to right
		{
			//			printf("Goes right\n");

			if(tempNode->right == NULL)
			{
				newNode->father = tempNode;
				tempNode->right = newNode;
				break;
			}
			else
			{
				tempNode = tempNode->right;
				continue;
			}
		}
		else //Goes to left
		{
			//			printf("Goes left\n");

			if(tempNode->left == NULL)
			{
				newNode->father = tempNode;
				tempNode->left = newNode;
				break;
			}
			else
			{
				tempNode = tempNode->left;
				continue;
			}
		}
	}
}

void emOrdem(tree_t* root)
{
	if(root != NULL)
	{
		emOrdem(root->left);
		printf(" %d ", root->val);
		emOrdem(root->right);
	}
}

void preOrdem(tree_t* root)
{
	if(root != NULL)
	{
		printf(" %d ", root->val);
		preOrdem(root->left);
		preOrdem(root->right);
	}
}

void posOrdem(tree_t* root)
{
	if(root != NULL)
	{
		posOrdem(root->left);
		posOrdem(root->right);
		printf(" %d ", root->val);
	}
}

void push(stack_t** stack, tree_t* val)
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

tree_t pop(stack_t** stack)
{
	stack_t* nodeToRemove;
	char result;

	if(*stack == NULL)
		return -1;

	nodeToRemove = *stack;
	*stack = (*stack)->below;

	result = nodeToRemove->val;

	free(nodeToRemove);

	return result;
}

void emOrdemIte(tree_t* root)
{
	tree_t* tempNode;
	stack_t* stack;

	tempNode = root;

	while(tempNode != NULL)
	{
		if(tempNode->left != NULL)
		{
			//Push and goes left
			push(&stack, tempNode);
			tempNode = tempNode->left;
			continue;
		}

		if(tempNode->right != NULL)
		{
			//Push and goes right
			push(&stack, tempNode);
			tempNode = tempNode->right;
			continue;
		}

		//No children, pop
		printf(" %d ", tempNode->val);
		tempNode = tempNode->father;
	}
}

int main( void )
{
	tree_t* root = NULL;

	add(&root, 5);
	add(&root, 3);
	add(&root, 2);
	add(&root, 5);
	add(&root, 7);
	add(&root, 8);

	emOrdem(root);
	printf("\n");
	preOrdem(root);
	printf("\n");
	posOrdem(root);

	return 0;
}
