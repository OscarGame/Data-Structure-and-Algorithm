#include "index.h"

#ifdef _STACK_POINTER_

typedef int elementtype;


struct node {
	elementtype val ;
	node *next ;
}; 

typedef node *STACK;


void MakeNull(STACK &S)
{	
	S=new node;
	S->next=NULL;
}

void Push(elementtype x, STACK &S)
{
	STACK stk;
	stk=new node;
	stk->val=x;
	stk->next=S->next;
	S->next=stk;
}

void Pop(STACK &S)
{
	STACK stk;
	if(S->next)
	{
		stk=S->next;
		S->next=stk->next;
		delete stk;
	}
}

elementtype Top(STACK S)
{
	if(S->next)
		return(S->next->val);
	else
		return NULL;
}

boolean Empty(STACK S)
{
	if(S->next)
		return FALSE;
	else
		return TRUE;
}

void main()
{
	STACK S;
	MakeNull(S);
	Push(2, S);
	Push(3, S);
	Push(4, S);
	while(S->next!=NULL)
	{
		cout<<Top(S)<<endl;
		Pop(S);
	}

}

#endif