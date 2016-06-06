#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include "index.h"
#include "stack.h"

#ifdef BINARYTREE

// ����������������ʾ
struct node {
	struct node *lchild ;
	struct node *rchild ;
	datatype data ;
};

typedef struct node * BTREE ;

void Empty(BTREE BT);
BOOLEAN IsEmpty(BTREE BT );
BTREE CreateBT(datatype v, BTREE LT , BTREE RT );
BTREE Lchild( BTREE BT );
BTREE Rchild ( BTREE BT );
datatype Data ( BTREE BT );

#endif

#endif