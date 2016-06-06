//静态链表有表头，表头无元素
#include<iostream>
using namespace std;

#define maxsize 100
typedef int elementtype;

typedef struct {
	elementtype element ;
	int next ;
} spacestr; /*结点类型*/

spacestr SPACE[ maxsize ] ;/*存储池*/

typedef int position, cursor;
cursor available;/* 标识线性表/空闲池*/

void Initialize()
{
	/* 依次链接池中结点*/
	for (int j=0; j<maxsize-1; j++ )
		SPACE[j].next=j+1;
	SPACE[j].next=-1;/* 最后一个接点指针域为空*/
	available=0;/* 标识线性表,将所有存储池中的结点设置为空闲，avilable为头结点，不利用*/
}

// 可用空间的分配操作,从空闲链中获取一个结点
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
}/* 将空闲池头结点的下一个节点从空闲池中删除*/

void FreeNode(cursor q) //delete q;
{ 
	SPACE [ q ].next =SPACE[available].next ;
	SPACE[available].next = q ;
}/* 将q指向的节点放回池中*/

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

//创建静态链表
void Create(cursor M)
{
	elementtype input;
	position p = M;
	while(1)
	{
		cout<<"请输入静态链表的值，输入-1结束："<<endl;
		cin>>input;
		if(input != -1)
		{
			Insert(input,p);
			p = SPACE[p].next;
		}
		else
			break;
	}
}

void Merge(cursor M,cursor N)
//连接两个链表,将N链表中的所有结点添加到M链表的后面，并将N链表的表头结点添加到空闲结点链表中
{
	position p;
	p=M;
	while(SPACE[p].next!=-1)
		p=SPACE[p].next;
	position q;
	q=SPACE[N].next;
	SPACE[p].next=q;
	FreeNode(N);
}

//输出静态链表
void Print(cursor M)
{
	position p;
	p = M;
	while(SPACE[p].next != -1)
	{
		cout<<SPACE[SPACE[p].next].element<<'\t';
		p = SPACE[p].next;
	}
	cout<<endl;
}
void main() 
{ 
	spacestr s;
	Initialize();
	position p=GetNode();

	cursor M=GetNode();
	SPACE[M].next = -1;//将链表表尾指向空
	cursor N=GetNode();
	SPACE[N].next = -1;

	cout<<"创建静态链表M："<<endl;
	Create(M);
	Print(M);
    cout<<"创建静态链表N："<<endl;
	Create(N);
	Print(N);
	cout<<"将M和N合并后："<<endl;
	Merge(M,N);
	Print(M);
} 
