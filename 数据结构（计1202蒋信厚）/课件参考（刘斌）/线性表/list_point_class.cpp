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

	/*���Ա����*/
	typedef celltype *LIST;

	/*λ����*/
	typedef celltype *position;

} ; /*�����*/

position End ( LIST L)
{ 
	position q ;
	q = L ;
	while ( q->next != NULL ) 
		q = q->next ;
	return ( q ) ;
} //ʱ�临���ԣ�O(n)

void Insert(elementtype x, position p, LIST &L )
{ 
	position q ;
	q = new celltype ;
	q->element = x ;
	q->next = p->next ;
	p->next = q ;
} //ʱ�临���ԣ�O(1)

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
} //ʱ�临���ԣ�O(n)

elementtype Retrieve( position p , LIST L )
{
	return ( p->next ->element );
} //ʱ�临���ԣ�O(1)

void Delete( position p, LIST &L )
{ 
	position q ;
	if ( p->next != NULL )
	{ 
		q = p->next ;
		p->next = q->next ;
		delete q ; 
	}
} //ʱ�临���ԣ�O(1)

position Previous ( position p, LIST L )
{ 
	position q ;
	if ( p == L->next )
		error ("������ǰ��Ԫ�أ�");
	else
	{ q = L ;
		while ( q->next != p ) q = q->next ;
		return q ;
	} 
} //ʱ�临�Ӷ�O(n)

position Next ( position p, LIST L )
{ 
	position q ;
	if ( p->next == NULL )
	error ("�����ں��Ԫ�أ�");
	else
	{ 
		q = p->next;
		return q ;
	}
} //ʱ�临�Ӷ�O(1)

position MakeNull ( LIST &L )
{
	L = new celltype ;
	L->next = NULL;
	return L ;
} //ʱ�临���ԣ�O(1)

position First ( LIST L )
{
	return L;
} //ʱ�临���ԣ�O(1)

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