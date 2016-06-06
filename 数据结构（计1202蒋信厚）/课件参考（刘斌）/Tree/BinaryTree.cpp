#include "BinaryTree.h"

#ifdef BINARYTREE

void visit(datatype d)
{
	cout<<d;
}

void Empty(BTREE BT)
{
	BT=NULL;
}

BOOLEAN IsEmpty(BTREE BT )
{
	if(BT==NULL)
		return TRUE;
	return FALSE;
}

BTREE CreateBT(datatype v, BTREE ltree , BTREE rtree )
{
	BTREE root;
	root = new node;
	root ->data = v; 
	root ->lchild = ltree; 
	root ->rchild = rtree;
	return root;
}

//��������������еĸ����
BTREE CreateBtree(BTREE & T, char *&str)
{ 
	char ch;
	ch=*str++;

	if ( ch == '#' ) T = NULL ;
	else{ 
		if ( !(T = new node ) ) 
			exit(1) ;
		T->data = ch ;
	CreateBtree ( T -> lchild, str ) ;
	CreateBtree ( T -> rchild, str ) ;
	}
	return T;
}

BTREE Lchild( BTREE BT )
{
	return BT->lchild;
}

BTREE Rchild ( BTREE BT )
{
	return BT->rchild;
}

datatype Data ( BTREE BT )
{
	return BT->data;
}

//�ȸ�����
void PreOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
   {
         visit ( Data( BT ) ) ;
         PreOrder ( Lchild ( BT ) ) ;
         PreOrder( Rchild ( BT ) ) ;
    }
}

//�и�����
void InOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
    { 
        InOrder ( Lchild ( BT ) ) ;
        visit ( Data ( BT ) ) ;
        InOrder ( Rchild( BT ) ) ;
    }
}

//�������
void PostOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
    { 
        PostOrder( Lchild ( BT ) ) ;        
        PostOrder( Rchild( BT ) ) ;
        visit ( Data ( BT ) ) ;
    }
}

// �и������ķǵݹ��㷨
void NInOrder(BTREE  BT )
{    
	STACK S ; 
	BTREE T=BT ;
	MakeNull( S ) ;
	while ( !IsEmpty( T ) || Empty ( S ) )
		if ( !IsEmpty ( T ) )
		{    
			Push( T ,S );
			T =  Lchild ( T ) ; 
		}
		else
		{    
			T = Top ( S ); 
			Pop ( S ) ;
			visit( Data( T ) ) ;
			T = Rchild ( T ) ; 
		}
}

//�����Ԫ���������ĵݹ��㷨
int Count ( BTREE T )
{
	if ( T == NULL ) 
		return 0;
	else 
		return 1 + Count ( T->lchild )+ Count ( T->rchild );
}


//���Ԫ���߶ȵĵݹ��㷨
int Height (BTREE T )
{ 
	if ( T == NULL ) 
		return 0;
	else 
	{
		int m = Height ( T->lchild );
		int n = Height ( T->rchild ) ;
		return (m > n) ? (m+1) : (n+1);
	}
}

//ɾ����Ԫ���ĵݹ��㷨
void destroy ( BTREE T )
{
	if ( T != NULL ) 
	{
		destroy ( T->lchild );
		destroy ( T->rchild );
		delete T;
	}
}

//�ж����ö������Ƿ�ȼ�
int Equal(BTREE firstbt , BTREE secondbt )
{   
	int x ;
	x = 0 ;
	if ( IsEmpty(firstbt) && IsEmpty(secondbt) )
		x = 1 ;
	else if ( ! IsEmpty( firstbt ) && ! IsEmpty( secondbt ) )
		if ( Data( firstbt ) == Data( secondbt ) )
		  if ( Equal( Lchild( firstbt ) , Lchild( secondbt ) ) )
			  x= Equal( Rchild( firstbt ) , Rchild( secondbt) )
	return( x ) ;
} /* EQUAL */

//�������ĸ���
BTREE CopyBT( BTREE oldtree )
{   
	BTREE temp ;
	if ( oldtree != NULL )
	{   
		temp = new Node ;
		temp -> lchild = CopyBT( oldtree->lchild ) ;
		temp -> rchild = CopyBT( oldtree->rchild ) ;
		temp -> data = oldtree->data ;
		return ( temp );
	}
	return ( NULL ) ;
} /* CopyBT */


void main()
{
	BTREE T, T1;

	T=CreateBT('f', NULL, NULL);
	T=CreateBT('d', T, NULL);
	T1=CreateBT('e', NULL, NULL);
	T=CreateBT('b', T, T1);
	T1=CreateBT('c', NULL, NULL);
	T=CreateBT('a', T, T1);

	PreOrder(T);
	cout<<endl;

	InOrder(T);
	cout<<endl;

	PostOrder(T);
	cout<<endl;
	
	NInOrder(T);
	cout<<endl;




	/*
	char *str="abdf###e##c##";
	T=CreateBtree(T,str);
	PreOrder(T);
	cout<<endl;
	*/

}

#endif