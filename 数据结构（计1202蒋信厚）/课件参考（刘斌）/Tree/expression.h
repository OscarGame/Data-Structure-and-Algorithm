#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "index.h"

#ifdef _EXPRESSION_

enum datatype1{logicalnot, logicaland, logicalor, logicaltrue, logicalfalse};


struct node{
	node *lchild;
	node *rchild;
	datatype data;
	BOOLEAN value;
};

typedef node *TREEEX;
void PoseOrderEval(TREEEX);
TREEEX CreateT(datatype1, TREEEX, TREEEX);

#endif

#endif