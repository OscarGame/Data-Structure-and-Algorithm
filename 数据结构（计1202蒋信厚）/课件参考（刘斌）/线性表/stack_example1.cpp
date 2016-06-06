#include "index.h"


#ifdef _STACK_EXAMPLE1_

#include "list_point.h"
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

boolean Judge(LIST head)
{
	STACK S;
	char e;
	MakeNull(S);
	LIST p=head->next;
	while(p!=NULL)
	{
		Push(p->element, S);
		p=p->next;
	}
	p=head->next;
	while(p!=NULL){
		e=Top(S);
		Pop(S);
		if(p->element==e)
			p=p->next;
		else
			break;
	}
	if(p==NULL)
		return TRUE;
	else 
		return FALSE;
}

void main()
{
	LIST L;
	position p=MakeNull(L);
	Insert('a', p, L);
	p=End(L);
	Insert('b', p, L);
	p=End(L);
	Insert('c', p, L);
	p=End( L);
	Insert('d', p, L);
	p=End(L);
	Insert('e', p, L);


	boolean b=Judge(L);
	if(b)
		cout<<"¶Ô³Æ"<<endl;
	else
		cout<<"²»¶Ô³Æ"<<endl;
	
}


#endif