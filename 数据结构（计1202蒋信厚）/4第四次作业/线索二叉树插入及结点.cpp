//�������������������ҽڵ�������
#include<iostream.h>
//���������������ڵ�����
 struct node{
	node * lchild;
	node * rchild;
	bool ltag;//���������Ƿ����
	bool rtag;
	char info;
};

 typedef node THTREE;
//������ڵ�
node * Next(node * P)
{
	node * Q = P->rchild;
	if(P->rtag==true)//���P�����������ڣ�����������Ϊ��������������
		while(Q->ltag==true)
			Q=Q->lchild;
		return Q;//����������������
}
//��ǰ�����
node *Previous(node *P)
{
	node *Q = P->lchild;
	if(P->ltag==true)//���P�����������ڣ�����ǰ�����Ϊ�����������ҽ��
		while(Q->rtag==true)
			Q=Q->rchild;
		return Q;//�����������ҽ��
}
//�и���������������
void ThInOrder(THTREE * HEAD)
{
	node * temp = HEAD;
	cout<<"�и���������������Ϊ��"<<endl;
	do{
		temp=Next(temp);
		if(temp!=HEAD)
			cout<<temp->info<<" ";
	}while(temp!=HEAD);
}
//�Ҳ�����
void RInsert(node * S,node * R)
{
	node * W;
	R->rchild=S->rchild;
	R->rtag=S->rtag;
	R->lchild=S;
	R->ltag=false;

	S->rchild=R;
	S->rtag=true;

	if(R->rtag==true)//���������������
	{
		W=Next(R);
		W->lchild=R;//���ұ߲���Ľ��R�ĺ���������ָ��R
	}
}
//�������
void LInsert(node * S,node * L)
{
	node * W;
	L->lchild=S->lchild;
	L->ltag=S->ltag;
	L->rtag=false;
	L->rchild=S;

	S->lchild=L;
	S->ltag=true;

	if(L->ltag == true)//���S������������
	{
		W = Previous(L);
		W->rchild = L;//����߲���Ľ��L��ǰ�����Һ���ָ��L
	}
}
/*
//����������???
void LChildInsert(THTREE * P,THTREE * Q)
{
	if(Q->ltag=false)
	{
		Q->lchild=P->lchild;
		Q->ltag=P->ltag;
	}
	P->lchild=Q;
	P->ltag=true;
}
*/

void main()
{
//HEADΪͷ��㣬AΪ���ڵ�
node * HEAD= new node;//ͷ���
node * A=new node;//���ڵ�
HEAD->info='!';
A->info='A';

HEAD->rchild=A;
HEAD->lchild=HEAD;
HEAD->rtag=true;
HEAD->ltag=true;

A->lchild=HEAD;
A->rchild=HEAD;
A->rtag=false;
A->ltag=false;

node * B = new node;//����
B->info='B';
node * C = new node;//�Һ���
C->info='C';
//��������������BAC
LInsert(A,B);
RInsert(A,C);
ThInOrder(HEAD);
cout<<endl;
//�ڽ��A��߲�����D,�ұ߲�����E
node * D = new node;
D->info = 'D';
node * E = new node;
E->info = 'E';
LInsert(A,D);
RInsert(A,E);
ThInOrder(HEAD);
cout<<endl;
delete A;
delete B;
delete C;
delete D;
delete E;
}