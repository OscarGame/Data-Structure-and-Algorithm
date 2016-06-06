//带头结点的双向链表h，设计一个算法用于查找第一个元素之为x的结点，并将其与其前驱结点进行交换。
#include<iostream>
using namespace std;
typedef int Elementtype;

struct celltype{
	Elementtype element;//数据域
	celltype *previous,*next;//前驱和后驱
};
typedef celltype *position;//位置的型
typedef celltype *DLIST;//双向链表的型

//插入元素,在p后面插入， 根据p后面有没有结点分为表尾插入和表中插入
void insert(position p,Elementtype x)
{
	if(p->next){
	position q = new celltype;
	q->element = x;
	q->next = p->next;
	q->previous = p;
	p->next->previous = q;
	p->next = q;
	}
	else
	{
		position q = new celltype;
		q->element = x;
		q->next = p->next;
		q->previous = p;
		p->next = q;
	}
}

//删除中间结点
void Delete(position p)
{
	if(p->next != NULL && p->previous != NULL)//删除的不是头尾结点
	{
		p->previous->next = p->next;
		p->next->previous = p->previous;
		delete p; 
	}
	else
		cout<<"头尾结点不是中间结点，不能删除！"<<endl;
}

void create(DLIST &head)//创建双向链表
{
	head->previous = NULL;//让头结点的前驱指向自己
	head->next = NULL;
	position p = head;
	int x=0,i=1;
	while(1){
	cout<<"请输入第"<<i++<<"个插入的元素（输入-1结束创建）："<<endl;
	cin>>x;
	if(x !=-1)
	{
		insert(p,x);
		p = p->next;
	}
	else
		break;
	}
}

void print(DLIST head)//输出链表元素
{
	position temp = head;
	while (temp->next) 
	{
		temp=temp->next;
		cout<<temp->element<<'\t';
	}
	cout<<endl;
}

int swap(Elementtype x,DLIST &head)//查找交换
{
	position temp,L;
	temp = head;
	while (temp->next)
	{
		temp=temp->next;
		if (temp->element==x&&temp->previous!=head)//元素匹配并且前驱不能是头结点
		{
			L = temp->previous;
			L->previous->next = temp;
			temp->previous = L->previous;
			L->next = temp->next;
			temp->next->previous = L;
			L->previous = temp;
			temp->next = L;
			return 1;
		}
	}
	return 0;
}

void main()
{
	DLIST head = new celltype;
	create(head);
	print(head);
	Elementtype x;
	cout<<"请输入你想查找的元素："<<endl;
	cin>>x;
	if(swap(x,head))
	{
		cout<<"查找交换成功！"<<endl;
		print(head);
	}
	else
		cout<<"查找失败！"<<endl;
}