#include "queue_pointer.h"

#ifdef _QUEUE_POINTER_

void main()
{
	QUEUE Q;
	MAKENULL(Q);
	ENQUEUE(2,Q);
	ENQUEUE(4,Q);
	ENQUEUE(6,Q);
	ENQUEUE(8,Q);
	while(!EMPTY(Q))
	{
		cout<<FRONT(Q)->element<<endl;
		DEQUEUE(Q);
	}
	
}

#endif