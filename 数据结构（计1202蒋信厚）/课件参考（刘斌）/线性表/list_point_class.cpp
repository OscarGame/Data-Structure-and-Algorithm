#include "index.h"

#ifdef _LIST_POINT_CLASS_

typedef int elementtype;

void error(char e[50])
{
	cout<<e<<endl;
}

class celltype {
	elementtype element ;
	celltype *next ;
	position END();
	void Insert(elementtype, posit

	/*线性表的型*/
	typedef celltype *LIST;

	/*位置型*/
	typedef celltype *position;

} ; /*结点型*/

position End ( LIST L)
{ 
	position q ;
	q = L ;
	while ( q->next != NULL ) 
		q = q->next ;
	return ( q ) ;
} //时间复杂性：O(n)

void Insert(elementtype x, position p, LIST &L )
{ 
	position q ;
	q = new celltype ;
	q->element = x ;
	q->next = p->next ;
	p->next = q ;
} //时间复杂性：O(1)

position Locate( elementtype x, LIST L )
{ 
	position p ;
	p = L ;
	while ( p->next != NULL )
		if ( p->next->element == x )
			return p ;
		else
			p = p->next;
	return p ;
} //时间复杂性：O(n)

elementtype Retrieve( position p , LIST L )
{
	return ( p->next ->element );
} //时间复杂性：O(1)

void Delete( position p, LIST &L )
{ 
	position q ;
	if ( p->next != NULL )
	{ 
		q = p->next ;
		p->next = q->next ;
		delete q ; 
	}
} //时间复杂性：O(1)

position Previous ( position p, LIST L )
{ 
	position q ;
	if ( p == L->next )
		error ("不存在前驱元素！");
	else
	{ q = L ;
		while ( q->next != p ) q = q->next ;
		return q ;
	} 
} //时间复杂度O(n)

position Next ( position p, LIST L )
{ 
	position q ;
	if ( p->next == NULL )
	error ("不存在后继元素！");
	else
	{ 
		q = p->next;
		return q ;
	}
} //时间复杂度O(1)

position MakeNull ( LIST &L )
{
	L = new celltype ;
	L->next = NULL;
	return L ;
} //时间复杂性：O(1)

position First ( LIST L )
{
	return L;
} //时间复杂性：O(1)

void Travel( LIST L )
{ 
	position p ;
	p = L->next ;
	while ( p != NULL)
	{ 
		cout << p->element<<endl;
		p = p->next ;
	}
}

void main()
{
	LIST L;
	
	position p=MakeNull(L);
	Insert(2, p, L);
	p=End(L);
	Insert(4, p, L);
	p=End(L);
	Insert(6, p, L);
	p=Locate(4, L);
	Insert(3, p, L);
	p=First(L);
	Insert(1, p, L);
	
	Travel(L);
}

#endif