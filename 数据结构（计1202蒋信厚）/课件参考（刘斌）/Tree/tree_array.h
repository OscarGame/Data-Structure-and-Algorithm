#ifndef _TREE_ARRAY_H_
#define _TREE_ARRAY_H_

#include "index.h"

#ifdef _TREE_ARRAY_

#define MAX_TREE_ARRAY 10
typedef char elementtype_tree_array;

struct nodeTR{
	int parent;
	elementtype_tree_array data;
};

typedef nodeTR TREE_ARRAY[MAX_TREE_ARRAY];

int LeftMostChild(TREE_ARRAY, int);
int RightSibling(TREE_ARRAY, int);
void PreOrder(TREE_ARRAY, int);
void CreateTreeArray(TREE_ARRAY &, nodeTR [], int );

#endif
#endif