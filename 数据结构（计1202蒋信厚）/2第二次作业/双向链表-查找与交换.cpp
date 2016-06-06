//��ͷ����˫������h�����һ���㷨���ڲ��ҵ�һ��Ԫ��֮Ϊx�Ľ�㣬����������ǰ�������н�����
#include<iostream>
using namespace std;
typedef int Elementtype;

struct celltype{
	Elementtype element;//������
	celltype *previous,*next;//ǰ���ͺ���
};
typedef celltype *position;//λ�õ���
typedef celltype *DLIST;//˫���������

//����Ԫ��,��p������룬 ����p������û�н���Ϊ��β����ͱ��в���
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

//ɾ���м���
void Delete(position p)
{
	if(p->next != NULL && p->previous != NULL)//ɾ���Ĳ���ͷβ���
	{
		p->previous->next = p->next;
		p->next->previous = p->previous;
		delete p; 
	}
	else
		cout<<"ͷβ��㲻���м��㣬����ɾ����"<<endl;
}

void create(DLIST &head)//����˫������
{
	head->previous = NULL;//��ͷ����ǰ��ָ���Լ�
	head->next = NULL;
	position p = head;
	int x=0,i=1;
	while(1){
	cout<<"�������"<<i++<<"�������Ԫ�أ�����-1������������"<<endl;
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

void print(DLIST head)//�������Ԫ��
{
	position temp = head;
	while (temp->next) 
	{
		temp=temp->next;
		cout<<temp->element<<'\t';
	}
	cout<<endl;
}

int swap(Elementtype x,DLIST &head)//���ҽ���
{
	position temp,L;
	temp = head;
	while (temp->next)
	{
		temp=temp->next;
		if (temp->element==x&&temp->previous!=head)//Ԫ��ƥ�䲢��ǰ��������ͷ���
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
	cout<<"������������ҵ�Ԫ�أ�"<<endl;
	cin>>x;
	if(swap(x,head))
	{
		cout<<"���ҽ����ɹ���"<<endl;
		print(head);
	}
	else
		cout<<"����ʧ�ܣ�"<<endl;
}