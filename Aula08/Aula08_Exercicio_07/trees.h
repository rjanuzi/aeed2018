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

void trees_binTreeAddNode(binTree_t** root, int val);
binTree_t* trees_genRandomBinTree(int len);
void trees_binTreePrint(binTree_t* root);
void trees_freeBinTree(binTree_t* root);

#endif /* _TREES_H */


