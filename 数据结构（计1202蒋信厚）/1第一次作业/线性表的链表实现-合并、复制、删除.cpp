//���Ա��ָ��ʵ��-���Ա�ĺϲ������ơ�ɾ��
#include<iostream>
using namespace std;

typedef int elementtype;//Ԫ������

struct celltype//����ڵ�
{
	elementtype elements;
	celltype *next;
};

typedef celltype *LIST;//���������
typedef celltype *position;//���Ա�ġ��͡���λ�õġ��͡���ͬ

position End(LIST L)
//����L��ָ�����һ���ڵ��ָ��
{
	position p;
	p=L;
	while(p->next!=NULL)
		p=p->next;
	return p;
}

void Insert(elementtype x, position p, LIST &L )
//����Ԫ��x�Ľڵ����p�ĺ���
{ 
	position q ;
	q = new celltype ;
	q->elements = x ;
	q->next = p->next ;
	p->next = q ;
} //ʱ�临���ԣ�O(1)

position Locate( elementtype x, LIST L )
//����Ԫ��x�����Ա��е�λ��
{ 
	position p ;
	p = L ;
	while ( p->next != NULL )
		if ( p->next->elements == x )
			return p ;
		else
			p = p->next;
	return p ;
} //ʱ�临���ԣ�O(n)

elementtype Retrieve( position p , LIST L )
{
	return p->next ->elements;
} //ʱ�临���ԣ�O(1)

void Delete( position p, LIST &L )
//ɾ��λ��p����һ���ڵ�
{ 
	position q ;
	if ( p->next != NULL )
	{ 
		q = p->next ;
		p->next = q->next ;
		delete q ; 
	}
} //ʱ�临���ԣ�O(1)

position Previous ( position p, LIST L )
//����λ��p��ǰ��Ԫ��
{ 
	position q ;
	if ( p == L->next )
		cout<<"������ǰ��Ԫ�أ�"<<endl;
	else
	{ q = L ;
		while ( q->next != p )
			q = q->next ;
		return q ;
	} 
} //ʱ�临�Ӷ�O(n)

position Next ( position p, LIST L )
//����λ��p�ĺ���Ԫ��
{ 
	position q ;
	if ( p->next == NULL )
	cout<<"�����ں��Ԫ�أ�"<<endl;
	else
	{ 
		q = p->next;
		return q ;
	}
} //ʱ�临�Ӷ�O(1)

position MakeNull ( LIST &L )
{
	L = new celltype ;
	L->next = NULL;
	return L ;
} //ʱ�临���ԣ�O(1)

position First ( LIST L )
{
	return L;
} //ʱ�临���ԣ�O(1)

void Travel( LIST L )//�������Ա�Ԫ��
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
//�ϲ��������Ա�(����)����L1��L2�ϲ���L��
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
//��������
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
//ɾ��ָ��Ԫ�صĽڵ�
int Delete(LIST &L,int x)
{
	int m=1;//ָ��Ԫ�������Ա��е�λ��
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
	return -1;//������Ԫ��x
}

void Read(LIST &L,int i)
//��������
{
	cout<<"�������"<<i<<"�����Ա�"<<endl;
	LIST p1=0,p2=0;
	elementtype x;
	for(;;)
	{
		cout<<"����������(-1��Ϊ������־):";
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
//���
{
	position p=L;
	for(;p;p=p->next)
		cout<<p->elements<<'\t';
	cout<<endl;
}

void main()
{
	cout<<"���β��Ե�����Ϊint"<<endl;
	LIST L=NULL,L1=NULL,L2=NULL;
	Read(L1,1);
	cout<<"L1��Ԫ��Ϊ��"<<endl;
	Write(L1);
	Read(L2,2);
	cout<<"L2��Ԫ��Ϊ��"<<endl;
	Write(L2);
	Merge(L,L1,L2);
	cout<<"L1,L2�ϲ���L��Ԫ��Ϊ��"<<endl;
	Write(L);
/*
	LIST L=NULL,L1=NULL;
	read(L);
	cout<<"ԭ�е�Ԫ�أ�";
	write(L);
	copy(L1,L);
	cout<<"����֮���Ԫ�أ�";
	write(L1);

  	LIST head=NULL;
	read(head);
	cout<<"ɾ��ǰ��";
	write(head);
	cout<<"������Ҫɾ�������ݣ�";
	Elementtype x;
	cin>>x;
	int m=Delete(head,x);
	cout<<"ɾ����";
	write(head);
	if(m==-1)
		cout<<"��Ҫɾ������������"<<endl;
	else
		cout<<"��Ҫɾ�������ǵ�"<<m<<"��"<<endl;
  */
}
