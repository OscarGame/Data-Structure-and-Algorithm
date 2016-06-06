//��̬�����б�ͷ����ͷ��Ԫ��
#include<iostream>
using namespace std;

#define maxsize 100
typedef int elementtype;

typedef struct {
	elementtype element ;
	int next ;
} spacestr; /*�������*/

spacestr SPACE[ maxsize ] ;/*�洢��*/

typedef int position, cursor;
cursor available;/* ��ʶ���Ա�/���г�*/

void Initialize()
{
	/* �������ӳ��н��*/
	for (int j=0; j<maxsize-1; j++ )
		SPACE[j].next=j+1;
	SPACE[j].next=-1;/* ���һ���ӵ�ָ����Ϊ��*/
	available=0;/* ��ʶ���Ա�,�����д洢���еĽ������Ϊ���У�avilableΪͷ��㣬������*/
}

// ���ÿռ�ķ������,�ӿ������л�ȡһ�����
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
}/* �����г�ͷ������һ���ڵ�ӿ��г���ɾ��*/

void FreeNode(cursor q) //delete q;
{ 
	SPACE [ q ].next =SPACE[available].next ;
	SPACE[available].next = q ;
}/* ��qָ��Ľڵ�Żس���*/

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

//������̬����
void Create(cursor M)
{
	elementtype input;
	position p = M;
	while(1)
	{
		cout<<"�����뾲̬�����ֵ������-1������"<<endl;
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
//������������,��N�����е����н����ӵ�M����ĺ��棬����N����ı�ͷ�����ӵ����н��������
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

//�����̬����
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
	SPACE[M].next = -1;//�������βָ���
	cursor N=GetNode();
	SPACE[N].next = -1;

	cout<<"������̬����M��"<<endl;
	Create(M);
	Print(M);
    cout<<"������̬����N��"<<endl;
	Create(N);
	Print(N);
	cout<<"��M��N�ϲ���"<<endl;
	Merge(M,N);
	Print(M);
} 
