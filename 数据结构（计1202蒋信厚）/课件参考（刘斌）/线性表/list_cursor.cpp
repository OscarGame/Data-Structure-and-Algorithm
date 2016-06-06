#include "index.h"

#ifdef _LIST_CURSOR_

#define maxsize 100
typedef int elementtype;


typedef struct {
	elementtype element ;
	int next ;
} spacestr; /*结点类型*/

spacestr SPACE[ maxsize ] ;/*存储池*/

typedef int position, cursor;
cursor available;

void Initialize()
{
	int j;
	/* 依次链接池中结点*/
	for (j=0; j<maxsize-1; j++ )
		SPACE[j].next=j+1;

	SPACE[j].next=-1;	  /* 最后一个接点指针域为空*/
	
	available=0;		/* 标识线性表*/
}

// 可用空间的分配操作
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
}/* 从池中删除*/

void FreeNode(cursor q) //delete q;
{ 
	SPACE [ q ].next =SPACE[available].next ;
	SPACE[available].next = q ;
}/* 放回池中*/

// 在位置p后面插入元素值为x的结点
void Insert ( elementtype x, position p)
{ 
	position q ;
	q = GetNode( ) ;
	SPACE[ q ].element = x ;
	SPACE[ q ].next = SPACE[ p ].next ;
	SPACE[ p ].next = q ;
}

// 删除位置p后的一个结点
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