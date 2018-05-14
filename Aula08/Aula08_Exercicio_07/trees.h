/**
*	@file trees.h
*
*	@author Rafael B. Januzi
*	@date 14/05/2018
*
*	@brief This module contains some utility tree functions
*/

#ifndef _TREES_H
#define _TREES_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

typedef struct binTree_s {
	int val;
	struct binTree_s* right;
	struct binTree_s* left;
} binTree_t;

typedef struct avlTree_s {
	int val;
	struct avlTree_s* right;
	struct avlTree_s* left;
} avlTree_t;

void trees_binTreeAddNode(binTree_t** root, int val);
binTree_t* trees_genRandomBinTree(int len);
void trees_binTreePrint(binTree_t* root);
void trees_freeBinTree(binTree_t* root);

void trees_avlTreeAddNode(avlTree_t** root, int val);
avlTree_t* trees_genRandomAvlTree(int len);
void trees_avlTreePrint(avlTree_t* root);
void trees_freeAvlTree(avlTree_t* root);

#endif /* _TREES_H */


