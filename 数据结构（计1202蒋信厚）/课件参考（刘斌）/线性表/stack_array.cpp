#include "index.h"

#ifdef _STACK_ARRAY_

#define maxlength 100

typedef struct {
elementtype elements[maxlength];
int top ;
} STACK ;


void MAKENULL( STACK &S )
{ 
	S.top = 0 ; 
}

boolean EMPTY( STACK S )
{ 
	if ( S.top < 1 )
		return TRUE	 ;
	else
		return FALSE ;
}

elementtype TOP( STACK S )
{ 
	if( EMPTY( S ) )
		return NULL;
	else
		return ( S.elements[ S.top ] );
}

void POP( STACK &S )
{
	if ( EMPTY (S ) )
		error ( "Õ»Îª¿Õ" ) ;
	else
		S.top = S.top-1 ;
}

void PUSH ( elementtype x, STACK &S )
{
	if ( S.top == maxlength - 1 )
		error ( "Õ»ÒÑÂú" ) ;
	else
	{ 
		S.top = S.top + 1 ;
		S.elements[ S.top ] = x ;
	}
}

 void EDIT( )
{  
	STACK S;    char c ;
	MAKENULL ( S );
	cin.get(c) ;
	while ( c != '\n' )
	{ 
		if ( c == '#' )
			POP ( S );
		else if ( c == '@' )
			MAKENULL ( S );
		else 
			PUSH ( c , S );
		cin.get(c) ;
    }
	while(!EMPTY(S))
	{
		cout<<TOP(S);
		POP(S);
	}
	cout<<endl;   
}

 void main()
 {
	 EDIT();
 }

#endif