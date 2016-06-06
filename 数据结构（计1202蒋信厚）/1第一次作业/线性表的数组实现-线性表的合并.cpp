//���Ա������ʵ��-���Ա�ĺϲ�
#include<iostream>
using namespace std;

#define maxlength 100
typedef int position;//λ������
typedef int Elementtype;//�±�����

struct LIST
{
	Elementtype elements[maxlength];
	int last;//���һ��Ԫ�ص��±�
};

position End(LIST L)//���Ա�ĳ���
{
	return (L.last+1);
}

void Insert(Elementtype x,position p,LIST &L)
//�ڱ�L��λ��p������x
{
	position q;
	if(L.last>=maxlength-1)
		cout<<"list is full"<<endl; 
	else if((p>L.last+1) || (p<1))
		cout<<"position does not exist"<<endl;
	else
	{
		for(q=L.last;q>=p;q--)
			L.elements[q+1]=L.elements[q];
		L.last=L.last+1;
		L.elements[p]=x;
	}
}

void Delete(position p,LIST &L)
//ɾ��λ��p����Ԫ��
{
	position q;
	if((p>L.last+1) || (p<1))
		cout<<"position does not exist"<<endl; 
	else
	{
		L.last=L.last-1;
		for(q=p;q<=L.last;q++)
			L.elements[q]=L.elements[q+1];
	}
}

position Locate(Elementtype x,LIST L)
//����x�ڱ�L�е�λ��
{
	position q;
	for(q=0;q<L.last;q++)
		if(L.elements[q]==x)
			return q;
	return (L.last+1);	//x������
}

Elementtype Retrive(position p,LIST L)
//����L��λ��Ϊp��Ԫ��
{
	if((p<1) || (p>L.last+1))
	{
		cout<<"position does not exist"<<endl;
		return -1;
	}
	return L.elements[p];
}
//======================================================
//���������Ա�ϲ�
void Merge(LIST &L,LIST L1,LIST L2)
{
	position p,p1,p2;
	position len1=End(L1);//L1�ĳ���
	position len2=End(L2);//L2�ĳ���
	L.last=len1+len2-1;//�ϲ���L�����һ��Ԫ�ص�λ��
	p=p1=p2=0;
	for(;p1<len1;)//��L1��Ԫ��д��L
	{
		L.elements[p]=L1.elements[p1];
		p++;
		p1++;
	}
	for(;p2<len2;)//������L2��Ԫ��д��L
	{
		L.elements[p]=L2.elements[p2];
		p++;
		p2++;
	}
}

void Read(LIST &L,int i)
//�������Ա�
{
	cout<<"�������"<<i<<"�����Ա�ĳ��ȣ�";
	cin>>L.last;
	L.last--;
	cout<<"�������"<<i<<"�����Ա��Ԫ�أ�"<<endl;
	for(position p=0;p<=L.last;p++)
		cin>>L.elements[p];
}

void Write(LIST L)
//������Ա�
{
	cout<<"���Ա�ĳ���Ϊ��"<<End(L)<<endl;
	cout<<"���Ա��Ԫ��Ϊ��"<<endl;
	for(position p=0;p<=L.last;p++)
		cout<<L.elements[p]<<'\t';
	cout<<endl;
}


void main()
{
	cout<<"���β��Ե�����Ϊint"<<endl;
	LIST L,L1,L2;
	Read(L1,1);
	Read(L2,2);
	Merge(L,L1,L2);
	Write(L);
}