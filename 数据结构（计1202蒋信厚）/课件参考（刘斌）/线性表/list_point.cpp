#include "index.h"

#ifdef _LIST_POINT_



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