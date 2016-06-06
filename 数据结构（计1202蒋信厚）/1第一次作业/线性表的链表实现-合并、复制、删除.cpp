//线性表的指针实现-线性表的合并、复制、删除
#include<iostream>
using namespace std;

typedef int elementtype;//元素类型

struct celltype//链表节点
{
	elementtype elements;
	celltype *next;
};

typedef celltype *LIST;//单链表的型
typedef celltype *position;//线性表的“型”与位置的“型”相同

position End(LIST L)
//返回L中指向最后一个节点的指针
{
	position p;
	p=L;
	while(p->next!=NULL)
		p=p->next;
	return p;
}

void Insert(elementtype x, position p, LIST &L )
//创建元素x的节点插在p的后面
{ 
	position q ;
	q = new celltype ;
	q->elements = x ;
	q->next = p->next ;
	p->next = q ;
} //时间复杂性：O(1)

position Locate( elementtype x, LIST L )
//返回元素x在线性表中的位置
{ 
	position p ;
	p = L ;
	while ( p->next != NULL )
		if ( p->next->elements == x )
			return p ;
		else
			p = p->next;
	return p ;
} //时间复杂性：O(n)

elementtype Retrieve( position p , LIST L )
{
	return p->next ->elements;
} //时间复杂性：O(1)

void Delete( position p, LIST &L )
//删除位置p的下一个节点
{ 
	position q ;
	if ( p->next != NULL )
	{ 
		q = p->next ;
		p->next = q->next ;
		delete q ; 
	}
} //时间复杂性：O(1)

position Previous ( position p, LIST L )
//返回位置p的前驱元素
{ 
	position q ;
	if ( p == L->next )
		cout<<"不存在前驱元素！"<<endl;
	else
	{ q = L ;
		while ( q->next != p )
			q = q->next ;
		return q ;
	} 
} //时间复杂度O(n)

position Next ( position p, LIST L )
//返回位置p的后驱元素
{ 
	position q ;
	if ( p->next == NULL )
	cout<<"不存在后继元素！"<<endl;
	else
	{ 
		q = p->next;
		return q ;
	}
} //时间复杂度O(1)

position MakeNull ( LIST &L )
{
	L = new celltype ;
	L->next = NULL;
	return L ;
} //时间复杂性：O(1)

position First ( LIST L )
{
	return L;
} //时间复杂性：O(1)

void Travel( LIST L )//遍历线性表元素
{ 
	position p ;
	p = L->next ;
	while ( p != NULL)
	{ 
		cout << p->elements<<endl;
		p = p->next ;
	}
}

//=================================================
void Merge(LIST &L,LIST L1,LIST L2) 
//合并两个线性表(链表)，将L1，L2合并到L中
{
	position p1=0,p2=0,p3=0;
	for(p3=L1;p3;p3=p3->next)
	{
		p1=new celltype;
		p1->elements=p3->elements;
		if(L==0)
		{
			L=p1;
			p2=p1;
		}
		else
		{
			p2->next=p1;
			p2=p1;
		}
	}
	for(p3=L2;p3;p3=p3->next)
	{ 
		p1=new celltype;
		p1->elements=p3->elements;
		if(L==0)
		{
			L=p1;
			p2=p1;
		}
		else
		{
			p2->next=p1;
			p2=p1;
		}
	}
	p2->next=NULL;
}

//==============================================
//复制链表
void copy(LIST &L1,LIST L2)
{
	position p1=0,p2=0,p3=0;
	for(p3=L2;p3;p3=p3->next)
	{
		p1=new celltype;
		p1->elements=p3->elements;
		p1->next=NULL;
		if(L1==NULL)
		{
			L1=p1;
			p2=p1;
		}
		else
		{
			p2->next=p1;
			p2=p1;
		}
	}
	p2->next=NULL;
}

//=====================================================
//删除指定元素的节点
int Delete(LIST &L,int x)
{
	int m=1;//指定元素在线性表中的位置
	position p1=0,p2=0;
	if(L->elements==x)
	{
		p1=L;
		L=L->next;
		delete p1;
		return m;
	}
	else
	{
		p1=p2=L;
		while(p1->elements!=x && p1!=NULL)
		{
			p2=p1;
			m++;
			p1=p1->next;
		}
		if(p1->elements==x)
		{
			p2->next=p1->next;
			delete p1;
			return m;
		}
	}
	return -1;//不存在元素x
}

void Read(LIST &L,int i)
//输入数据
{
	cout<<"请输入第"<<i<<"个线性表"<<endl;
	LIST p1=0,p2=0;
	elementtype x;
	for(;;)
	{
		cout<<"请输入数据(-1作为结束标志):";
		cin>>x;
		if(x==-1) break;
		p1=new celltype;
		p1->elements=x;
		if(L==0)
		{
			L=p1;
			p2=p1;
		}
		else
		{
			p2->next=p1;
			p2=p1;
		}
	}
	p2->next=NULL;
}


void Write(LIST L)
//输出
{
	position p=L;
	for(;p;p=p->next)
		cout<<p->elements<<'\t';
	cout<<endl;
}

void main()
{
	cout<<"本次测试的类型为int"<<endl;
	LIST L=NULL,L1=NULL,L2=NULL;
	Read(L1,1);
	cout<<"L1的元素为："<<endl;
	Write(L1);
	Read(L2,2);
	cout<<"L2的元素为："<<endl;
	Write(L2);
	Merge(L,L1,L2);
	cout<<"L1,L2合并后L的元素为："<<endl;
	Write(L);
/*
	LIST L=NULL,L1=NULL;
	read(L);
	cout<<"原有的元素：";
	write(L);
	copy(L1,L);
	cout<<"复制之后的元素：";
	write(L1);

  	LIST head=NULL;
	read(head);
	cout<<"删除前：";
	write(head);
	cout<<"请输入要删除的数据：";
	Elementtype x;
	cin>>x;
	int m=Delete(head,x);
	cout<<"删除后：";
	write(head);
	if(m==-1)
		cout<<"需要删除的数不存在"<<endl;
	else
		cout<<"需要删除的数是第"<<m<<"个"<<endl;
  */
}
