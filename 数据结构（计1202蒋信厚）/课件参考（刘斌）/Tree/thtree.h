#ifndef _THTREE_H_
#define _THTREE_H_

#include "index.h"

#ifdef _THTREE_

struct node {
	datatype data ;
	node *lchild , *rchild ;
	BOOLEAN ltag , rtag ;  
};

typedef node* THTREE;

THTREE InNext( THTREE p);
THTREE InPre( THTREE p);
void ThInOrder( THTREE HEAD);
void RInsert ( THTREE S , THTREE R );
void LInsert ( THTREE S , THTREE R );
THTREE PreNext( THTREE p);

#endif

#endif