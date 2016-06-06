#include "index.h"

#ifdef _LIST_CURSOR_

#define maxsize 100
typedef int elementtype;


typedef struct {
	elementtype element ;
	int next ;
} spacestr; /*�������*/

spacestr SPACE[ maxsize ] ;/*�洢��*/

typedef int position, cursor;
cursor available;

void Initialize()
{
	int j;
	/* �������ӳ��н��*/
	for (j=0; j<maxsize-1; j++ )
		SPACE[j].next=j+1;

	SPACE[j].next=-1;	  /* ���һ���ӵ�ָ����Ϊ��*/
	
	available=0;		/* ��ʶ���Ա�*/
}

// ���ÿռ�ķ������
cursor GetNode() // q=new spacestr ;
{ 
	cursor p;
	if (SPACE[available].next ==-1)
		p=-1;
	else
	{ 
		p= SPACE[available].next ;
		SPACE[available].next =	SPACE[ p ].next ;
	}
	return p;
}/* �ӳ���ɾ��*/

void FreeNode(cursor q) //delete q;
{ 
	SPACE [ q ].next =SPACE[available].next ;
	SPACE[available].next = q ;
}/* �Żس���*/

// ��λ��p�������Ԫ��ֵΪx�Ľ��
void Insert ( elementtype x, position p)
{ 
	position q ;
	q = GetNode( ) ;
	SPACE[ q ].element = x ;
	SPACE[ q ].next = SPACE[ p ].next ;
	SPACE[ p ].next = q ;
}

// ɾ��λ��p���һ�����
void Delete ( position p)
{ 
	position q ;
	if ( SPACE[ p ].next != -1 )
	{ 
		q = SPACE[ p ].next ;
		SPACE[ p ].next = SPACE[ q ].next ;
		FreeNode( q ) ;
	}
}


void main()
{
	Initialize();
	position p=GetNode();
	Insert(2, p);	
	Insert(4, p);
	Insert(6, p);
	position q = GetNode();
	Insert(1, q);
	Insert(3, q);

}
#endif