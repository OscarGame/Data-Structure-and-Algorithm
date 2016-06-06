#include "index.h"

#ifdef _STACK_EXAMPLE_

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
		error ( "ջΪ��" ) ;
	else
		S.top = S.top-1 ;
}

void PUSH ( elementtype x, STACK &S )
{
	if ( S.top == maxlength - 1 )
		error ( "ջ����" ) ;
	else
	{ 
		S.top = S.top + 1 ;
		S.elements[ S.top ] = x ;
	}
}

boolean Correct(char ext[], int n)
{
	STACK S;
	char x;
	int j=0;
	MAKENULL(S);
	while(ext[j])
	{
		if(ext[j]=='(')
			PUSH('(', S);
		else if(ext[j]==')')
		{
			x=TOP(S);
			if(x=='(')
				POP(S);
			else
				return FALSE;
		}
		j++;
	}
	if(!EMPTY(S)) 
		return FALSE;
	else
		return TRUE;
}

 void main()
 {
	 boolean b=Correct("()()()()())",15);
	 if(b)
		 cout<<"�Ϸ�"<<endl;
	 else
		 cout<<"���Ϸ�"<<endl;
 }


#endif