
#include "index.h"

#ifdef _LIST_ARRAY_CLASS_

#define maxlength 100

typedef int elementtype;
typedef int position;


class LIST {
    elementtype elements[maxlength];
    int last;

public:
	LIST()
	{
		last=0;
	}

	void Insert(elementtype x, position p)
	{ 
		position q ;
		if (last >= maxlength)
			error("��������");
		else if (( p > last +1 ) || ( p < 1) )
			error("������Ч�Ĳ���λ�ã�");
		else {
			for ( q = last; q >= p; q -- )
				elements[ q + 1] = elements[ q ] ;
			last = last + 1 ;
			elements[ p ] = x ;
		}
	}   //ʱ�临�Ӷ�O(n)

	position Locate( elementtype x)
	{ 
		position q ;
		for ( q = 1; q <=last ; q++ )
			if ( elements[ q ] == x )
				return ( q ) ;
		return ( last + 1 );
	} //ʱ�临���ԣ�O(n)


	elementtype Retrieve( position p )
	{ 
		if ( p > last )
			error("ָ��Ԫ�ز����ڣ�") ;
		else
			return ( elements[ p ] ) ;
	} //ʱ�临�Ӷ�O(1)

	void Delete( position p )
	{ 
		position q ;
		if ( ( p >last ) || ( p < 1 ) )
			error ("ָ��λ�ò����ڣ�");
		else
		{ 
			last = last-1;
			for ( q = p ; q <= last ; q ++ )
				elements[ q ] = elements[ q + 1 ];
		}
	} //ʱ�临�Ӷ�O(n)

};

void main()
{
	LIST L;

	L.Insert(2, 1);
	L.Insert(3, 2);
	L.Insert(4, 3);
	L.Insert(5, 4);

	cout<<L.Retrieve(2)<<endl;

}


#endif