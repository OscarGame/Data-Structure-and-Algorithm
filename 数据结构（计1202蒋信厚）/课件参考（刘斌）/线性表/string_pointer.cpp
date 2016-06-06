#include "index.h"


#ifdef _STRING_POINTER_

#include "list_point.h"

typedef celltype *STRING;

void CreateString(char c[], int n, STRING &S)
{
	position p=MakeNull(S);
	for(int i=0; i<n; i++)
	{
		Insert(c[i], p, S);
		p=End(S);
	}
}

int Len(STRING S)
{
	int l=0;
	while(S->next!=NULL)
	{
		++l;
		S=S->next;
	}
	return l;
}

boolean IsNull(STRING S)
{
	if(S->next==NULL)
		return TRUE;
	else
		return FALSE;
}

STRING Concat(STRING S1, STRING S2)
{
	STRING tmp=S1;
	while(S1->next!=NULL) S1=S1->next;
	while(S2->next!=NULL)
	{		
		S1->next=S2->next;
		S1=S1->next;
		S2=S2->next;
	}
	S1->next=NULL;
	return tmp;
}

STRING Substr(STRING S, int m, int n)
{
	STRING tmp;
	MakeNull(tmp);
	STRING tmp1=tmp;

	if(m<1) m=1;
	else if(m>Len(S))
		return NULL;
	
	for(int i=0; i<m; i++)
	{
		S=S->next;
	}
	
	for(i=0; (i<n) && (S!=NULL); i++)
	{
		tmp->next=S;
		tmp=tmp->next;
		S=S->next;
	}
	tmp->next=NULL;
	return tmp1;
}

int Index ( STRING S, STRING S1 )
{
	STRING p, q, i ;
	int t ;
	if ( ( S1->next != NULL ) && ( S->next != NULL ) )
	{ 
		t = 1 ; i = p = S->next ; q = S1->next ;
		do {
			if ( p->element == q->element )
			{ 
				q = q->next ;
				if ( q == NULL ) 
					return( t ) ;
				p = p->next ;
			}
			else
			{ 
				t = t + 1 ; 
				i = i->next ;
				p = i ; 
				q = S1->next ;
			}
		} while ( p != NULL ) ;
	}
	return 0 ;
}

void main()
{
	STRING S, S1;
	CreateString("abcdefghijk", 11, S);
	CreateString("cde", 3, S1);

	cout<<Len(S1)<<endl;

	cout<<Index(S, S1)<<endl;

	S=Concat(S, S1);

	Travel(S);
	cout<<endl;
	Travel(Substr(S, 3, 7));
	
}


#endif