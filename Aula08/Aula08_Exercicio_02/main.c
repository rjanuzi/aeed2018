#include <stdio.h>
#include <stdlib.h>

typedef struct tree_s {
	int val;
	struct tree_s* right;
	struct tree_s* left;
	struct tree_s* father;
} tree_t;

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

void printEmOrdem(tree_t* root)
{
	if(root != NULL)
	{
		printEmOrdem(root->left);
		printf(" %d ", root->val);
		printEmOrdem(root->right);
	}
}

void printLeafs(tree_t* root)
{
	if(root != NULL)
	{
		if(root->left == NULL && root->right == NULL) //Print if is a leaf
			printf(" %d ", root->val);
		else //Skip two useless calls for each leaf
		{
			printLeafs(root->left);
			printLeafs(root->right);
		}
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

	printf("Leafs:");
	printLeafs(root);

	return 0;
}
