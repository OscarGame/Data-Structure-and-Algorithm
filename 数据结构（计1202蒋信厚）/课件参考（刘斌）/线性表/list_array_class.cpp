
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
			error("表已满！");
		else if (( p > last +1 ) || ( p < 1) )
			error("不是有效的插入位置！");
		else {
			for ( q = last; q >= p; q -- )
				elements[ q + 1] = elements[ q ] ;
			last = last + 1 ;
			elements[ p ] = x ;
		}
	}   //时间复杂度O(n)

	position Locate( elementtype x)
	{ 
		position q ;
		for ( q = 1; q <=last ; q++ )
			if ( elements[ q ] == x )
				return ( q ) ;
		return ( last + 1 );
	} //时间复杂性：O(n)


	elementtype Retrieve( position p )
	{ 
		if ( p > last )
			error("指定元素不存在！") ;
		else
			return ( elements[ p ] ) ;
	} //时间复杂度O(1)

	void Delete( position p )
	{ 
		position q ;
		if ( ( p >last ) || ( p < 1 ) )
			error ("指定位置不存在！");
		else
		{ 
			last = last-1;
			for ( q = p ; q <= last ; q ++ )
				elements[ q ] = elements[ q + 1 ];
		}
	} //时间复杂度O(n)

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