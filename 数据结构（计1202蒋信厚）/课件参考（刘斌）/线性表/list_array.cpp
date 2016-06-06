
#include "index.h"

#ifdef _LIST_ARRAY_

#define maxlength 100

typedef int elementtype;
typedef int position;

struct LIST {
    elementtype elements[maxlength];
    int last;
};


void Insert(elementtype x, position p, LIST &L)
{ 
	position q ;
	if (L.last >= maxlength)
		error("��������");
	else if (( p > L.last +1 ) || ( p < 1) )
		error("������Ч�Ĳ���λ�ã�");
	else {
		for ( q = L.last; q >= p; q -- )
			L.elements[ q + 1] = L.elements[ q ] ;
		L.last = L.last + 1 ;
		L.elements[ p ] = x ;
	}
}   //ʱ�临�Ӷ�O(n)

position Locate( elementtype x, LIST L )
{ 
	position q ;
	for ( q = 1; q <= L.last ; q++ )
		if ( L.elements[ q ] == x )
			return ( q ) ;
	return ( L.last + 1 );
} //ʱ�临���ԣ�O(n)


elementtype Retrieve( position p, LIST L )
{ 
	if ( p > L.last )
		error("ָ��Ԫ�ز����ڣ�") ;
	else
		return ( L.elements[ p ] ) ;
} //ʱ�临�Ӷ�O(1)

void Delete( position p , LIST &L)
{ 
	position q ;
	if ( ( p > L.last ) || ( p < 1 ) )
		error ("ָ��λ�ò����ڣ�");
	else
	{ 
		L.last = L.last-1;
		for ( q = p ; q <= L.last ; q ++ )
			L.elements[ q ] = L.elements[ q + 1 ];
	}
} //ʱ�临�Ӷ�O(n)

void main()
{
	LIST L;
	L.last=0;
	Insert(2, 1, L);
	Insert(3, 2, L);
	Insert(4, 3, L);
	Insert(5, 4, L);

	cout<<Retrieve(2, L)<<endl;

}


#endif