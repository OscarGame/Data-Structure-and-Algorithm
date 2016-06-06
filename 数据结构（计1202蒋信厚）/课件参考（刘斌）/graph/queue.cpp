#include "index.h"
#include "queue.h"

#ifdef _QUEUE_

void error(char *str)
{
	cout<<str<<endl;
}

void MAKENULL( QUEUE &Q )
{
	Q.front = new celltype ;
	Q.front->next = NULL ;
	Q.rear = Q.front ;
}

BOOLEAN EMPTY( QUEUE &Q )
{ 
	if ( Q.front == Q.rear )
		return TRUE ;
	else
		return FALSE ;
}

celltype *FRONT(QUEUE Q)
{
	if(Q.front==Q.rear)
		return NULL;
	else
		return Q.front->next;
}

void ENQUEUE ( que_elementtype x, QUEUE &Q )
{ 
	Q.rear->next = new celltype ;
	Q.rear = Q.rear->next ;
	Q.rear->element = x ;
	Q.rear->next = NULL ;
}

void DEQUEUE ( QUEUE &Q )
{ 
	celltype *temp ;
	if ( EMPTY( Q ) )
		error ("╤сапн╙©у") ;
	else { 
		temp = Q.front->next ;
		Q.front->next = temp->next ;
		delete temp ;
	
		if ( Q.front->next == NULL )
			Q.rear = Q.front ; 
	}
}

#endif