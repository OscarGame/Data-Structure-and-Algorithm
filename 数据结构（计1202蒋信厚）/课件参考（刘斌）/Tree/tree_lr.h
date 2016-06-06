#ifndef _TREE_LR_H_
#define _TREE_LR_H_

#include "index.h"
#ifdef _TREE_LR_

#define maxnodes_lr 10

typedef char datatype_lr;

int avail;

struct{
    datatype_lr data;
    int leftchild;
    int rightsibling;
    int parent;
}cellspace_lr[maxnodes_lr];

void ini_TREE_LR();
int Create_TREE_LR(datatype_lr v, int L, int r);
int root_LR();
int LeftMostChild(int n);
int RightSibling(int n);
void PreOrder(int n);

void visit(datatype_lr d);
datatype_lr Data(int n);

void print_LR();


#endif
#endif