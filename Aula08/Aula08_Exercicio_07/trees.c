#include "trees.h"

void trees_binTreeAddNode(binTree_t** root, int val)
{
	binTree_t* newNode;
	binTree_t* tempNode;

	newNode = malloc(sizeof(binTree_t));

	newNode->val = val;
	newNode->left = NULL;
	newNode->right = NULL;

	if(*root == NULL)
	{
		*root = newNode;
		return;
	}

	tempNode = *root;

	while(1)
	{
		if(val > tempNode->val) //Goes to right
		{
			if(tempNode->right == NULL)
			{
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
			if(tempNode->left == NULL)
			{
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

binTree_t* trees_genRandomBinTree(int len)
{
	binTree_t* root = NULL;
	int i;

	srand((unsigned) time(NULL));

	for(i = 0; i < len; i++)
		trees_binTreeAddNode(&root, (rand() % INT_MAX));

	return root;
}

void trees_binTreePrint(binTree_t* root)
{
	if(root != NULL)
	{
		trees_binTreePrint(root->left);
		printf(" %d ", root->val);
		trees_binTreePrint(root->right);
	}
}

void trees_freeBinTree(binTree_t* root)
{
	if(root != NULL)
	{
		if(root->left != NULL)
			trees_freeBinTree(root->left);

		if(root->right != NULL)
			trees_freeBinTree(root->right);

		free(root);
	}
}

void trees_avlTreeAddNode(avlTree_t** root, int val) {
	//TODO - Código atual é árvore binária
	avlTree_t* newNode;
	avlTree_t* tempNode;

	newNode = malloc(sizeof(avlTree_t));

	newNode->val = val;
	newNode->left = NULL;
	newNode->right = NULL;

	if(*root == NULL)
	{
		*root = newNode;
		return;
	}

	tempNode = *root;

	while(1)
	{
		if(val > tempNode->val) //Goes to right
		{
			if(tempNode->right == NULL)
			{
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
			if(tempNode->left == NULL)
			{
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

avlTree_t* trees_genRandomAvlTree(int len) {
	avlTree_t* root = NULL;
	int i;

	srand((unsigned) time(NULL));

	for(i = 0; i < len; i++)
		trees_avlTreeAddNode(&root, (rand() % INT_MAX));

	return root;
}

void trees_avlTreePrint(avlTree_t* root) {
	if(root != NULL)
	{
		trees_avlTreePrint(root->left);
		printf(" %d ", root->val);
		trees_avlTreePrint(root->right);
	}
}

void trees_freeAvlTree(avlTree_t* root) {
	if(root != NULL)
	{
		if(root->left != NULL)
			trees_freeAvlTree(root->left);

		if(root->right != NULL)
			trees_freeAvlTree(root->right);

		free(root);
	}
}
