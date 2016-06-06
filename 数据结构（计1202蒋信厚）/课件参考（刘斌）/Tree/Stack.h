#include "index.h"
#include "BinaryTree.h"

#define maxlength 100

typedef struct node *elementtype;


typedef struct {
elementtype elements[maxlength];
int top ;
} STACK ;

void error(char *str)
{
	cout<<str<<endl;
}

void MakeNull( STACK &S )
{ 
	S.top = 0 ; 
}

BOOLEAN Empty( STACK S )
{ 
	if ( S.top < 1 )
		return TRUE	 ;
	else
		return FALSE ;
}

elementtype Top( STACK S )
{ 
	if( Empty( S ) )
		return NULL;
	else
		return ( S.elements[ S.top ] );
}

void Pop( STACK &S )
{
	if ( Empty (S ) )
		error ( "Õ»Îª¿Õ" ) ;
	else
		S.top = S.top-1 ;
}

void Push ( elementtype x, STACK &S )
{
	if ( S.top == maxlength - 1 )
		error ( "Õ»ÒÑÂú" ) ;
	else
	{ 
		S.top = S.top + 1 ;
		S.elements[ S.top ] = x ;
	}
}