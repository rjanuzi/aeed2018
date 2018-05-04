#include <stdbool.h>
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

tree_t* findMostLeftInSubTree(tree_t* root)
{
	tree_t* tempNode;

	tempNode = root;

	while(tempNode != NULL)
	{
		if(tempNode->left == NULL)
			return tempNode;
		else
			tempNode = tempNode->left;
	}

	return NULL;
}

void removeRoot(tree_t** root)
{
	tree_t* newRoot;

	//Root is NULL or has no childs
	if((*root) == NULL || ((*root)->left == NULL && (*root)->right == NULL))
	{
		free((*root));
		*root = NULL;
		return;
	}

	if((*root)->left == NULL)
		newRoot = (*root)->right; //Has only a right child
	else
		if((*root)->right == NULL)
			newRoot = (*root)->left; //Has only a left child
		else {
			//Has left and right child
			newRoot = findMostLeftInSubTree((*root)->right);

			if((*root)->right != newRoot)
				newRoot->right = (*root)->right;
			else
				newRoot->right = NULL;

			newRoot->left = (*root)->left;
		}

	free((*root));
	newRoot->father = NULL;
	*root = newRoot;
}

bool removeNode(tree_t** root, int val)
{
	tree_t* nodeToRemove;
	tree_t* nodeToUse;

	if(*root == NULL)
		return false;

	nodeToRemove = *root;

	while(nodeToRemove != NULL) {

		if(nodeToRemove->val == val) {

			//If the finded node is the root
			if(nodeToRemove->father == NULL)
			{
				removeRoot(root);
				return true;
			}

			if(nodeToRemove->left == NULL && nodeToRemove->right == NULL) { //If is leaf
				if(nodeToRemove->father->left == nodeToRemove) //If the node to remove is a left child
					nodeToRemove->father->left = NULL;
				else
					nodeToRemove->father->right = NULL; //If its a right child
			} else
				if(nodeToRemove->right == NULL) { //If has just a left sub tree

					if(nodeToRemove->father->left == nodeToRemove) //If the node to remove is a left child
						nodeToRemove->father->left = nodeToRemove->left;
					else
						nodeToRemove->father->right = nodeToRemove->left; //If its a right child

					nodeToRemove->left->father = nodeToRemove->father;
				} else
					if(nodeToRemove->left == NULL) { //If has just a right sub tree

						if(nodeToRemove->father->left == nodeToRemove) //If the node to remove is a left child
							nodeToRemove->father->left = nodeToRemove->right;
						else
							nodeToRemove->father->right = nodeToRemove->right; //If its a right child

						nodeToRemove->right->father = nodeToRemove->father;
					}
					else { //If has 2 sub trees

						nodeToUse = findMostLeftInSubTree(nodeToRemove->right);

						if(nodeToUse->father == nodeToRemove)
							nodeToUse->right = NULL;
						else
							nodeToUse->right = nodeToRemove->right;

						nodeToUse->left = nodeToRemove->left;
						nodeToUse->father = nodeToRemove->father;
					}

			//Clear removed node memory allocation
			free(nodeToRemove);
			return true;
		}

		if(val > nodeToRemove->val)
			nodeToRemove = nodeToRemove->right; //Goes to right
		else
			nodeToRemove = nodeToRemove->left; //Or goes to left
	}

	return false;
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

	printf("\nEm ordem:");
	printEmOrdem(root);
	printf("\nRemove 2: %d", removeNode(&root, 2));
	printf("\nEm ordem:");
	printEmOrdem(root);
	printf("\nRemove 7: %d", removeNode(&root, 7));
	printf("\nEm ordem:");
	printEmOrdem(root);
	printf("\nRemove 10: %d", removeNode(&root, 10));
	printf("\nEm ordem:");
	printEmOrdem(root);
	printf("\nRemove 5: %d", removeNode(&root, 5));
	printf("\nEm ordem:");
	printEmOrdem(root);

	return 0;
}
