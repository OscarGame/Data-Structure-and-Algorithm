#include "thtree.h"

#ifdef _THTREE_

void visit(datatype d)
{
	cout<<d;
}

//求参数结点p的中序的后继结点
THTREE InNext( THTREE p)
{    
	THTREE Q=p->rchild ;
	if (p->rtag == TRUE )
		while(Q->ltag == TRUE)
			Q = Q->lchild ;
	return ( Q ) ;
}

//求参数结点p的中序的前导结点
THTREE InPre( THTREE p)
{    
	THTREE Q ;
	Q=p->lchild ;
	if (p->ltag == TRUE )
		while(Q->rtag == TRUE)
			Q = Q->rchild ;
	return ( Q ) ;
}

//利用InNext算法，中序遍历线索二叉树
void ThInOrder( THTREE HEAD)
{    
	THTREE temp ;
    temp = HEAD ;
    do {
		temp = InNext ( temp ) ;
		if ( temp != HEAD )
			visit ( temp -> data ) ;
    } while ( temp != HEAD ) ;
}

//中序线索二叉树的插入算法，参数R作为参数S的右儿子
void RInsert ( THTREE S , THTREE R )
{   
	THTREE w ;
	R->rchild = S->rchild ;
	R->rtag = S->rtag ;
	R->lchild = S ;
	R->ltag = FALSE ;
	S->rchild = R ;
	S->rtag = TRUE ;
	if ( R->rtag == TRUE )
	{  
		w = InNext( R ) ;
		w->lchild = R ; 
	}
}

//中序线索二叉树的插入算法，参数R作为参数S的左儿子
void LInsert ( THTREE S , THTREE R )
{   
	THTREE w ;
	R->lchild = S->lchild ;
	R->ltag = S->ltag ;
	R->rchild = S ;
	R->rtag = FALSE ;
	S->lchild = R ;
	S->ltag = TRUE ;
	if ( R->ltag == TRUE )
	{  
		w = InPre( R ) ;
		w->rchild = R ; 
	}
}

//求中序线索二元树中结点p 先序顺序的后继结点p*的算法
THTREE PreNext( THTREE p)
{    
	THTREE Q ;
	if (p->ltag == TRUE )
		Q=p->lchild ;
	else
	{   
		Q = p;
		while(Q->rtag == FALSE)
			Q = Q->rchild ;
		Q = Q->rchild ;
	}
	 return ( Q ); 
}

//创建一个结点，其左孩子指针和右孩子指针都指向该结点本身
void create_a_node(THTREE &N, datatype d)
{
	
	N=new node;
	N->data=d;
	N->lchild=NULL;
	N->rchild=NULL;
	N->ltag=FALSE;
	N->rtag=FALSE;
}

void main()
{
	THTREE H=NULL, S=NULL, R=NULL;
	create_a_node(H, ' ');
	H->rtag=TRUE;
	H->ltag=FALSE;
	H->lchild=H;
	H->rchild=H;
	
	create_a_node(S, 'a');
	LInsert(H, S);
	create_a_node(R, 'c');
	RInsert(S, R);
	create_a_node(R, 'b');
	LInsert(S, R);
	create_a_node(S, 'd');
	LInsert(R, S);
	create_a_node(S, 'e');
	RInsert(R, S);
	create_a_node(R, 'f');
	RInsert(S, R);

	ThInOrder(H);
	cout<<endl;
}

#endif