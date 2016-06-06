//���е�ָ��ʵ��
#include<iostream>
using namespace std;

#define maxlength 20
typedef int que_elementtype;//����Ԫ������

//����Ԫ�ؽڵ�����
struct celltype {
	que_elementtype element;
	celltype *next;
};
//���нṹ��
struct QUEUE {
	celltype *front;
	celltype *rear;
};
//frontָ��ͷ��㣬rearָ�����һ��Ԫ�أ���rearҲָ��ͷ���ʱ����Ϊ��

/*
��������
void error(char *str);
void MAKENULL( QUEUE &Q );
BOOLEAN EMPTY( QUEUE &Q );
celltype *FRONT(QUEUE Q);
void ENQUEUE ( que_elementtype x, QUEUE &Q );
void DEQUEUE ( QUEUE &Q );
*/

//���л�������
void MAKENULL( QUEUE &Q )
{
	Q.front = new celltype ;
	Q.front->next = NULL ;
	Q.rear = Q.front ;//����Ϊ��
}

bool EMPTY( QUEUE &Q )//�ж��Ƿ�Ϊ��
{ 
	if ( Q.front == Q.rear )
		return true ;
	else
		return false ;
}

celltype *FRONT(QUEUE Q)//���ص�һ��Ԫ�ؽڵ�
{
	if(Q.front==Q.rear)
		return NULL;
	else
		return Q.front->next;
}

void ENQUEUE ( que_elementtype x, QUEUE &Q )//��x�����β
{ 
	Q.rear->next = new celltype ;
	Q.rear = Q.rear->next ;
	Q.rear->element = x ;
	Q.rear->next = NULL ;
}

void DEQUEUE ( QUEUE &Q )//ɾ�����еĵ�һ��Ԫ��
{ 
	celltype *temp ;//��ʱԪ�ؽڵ�
	if ( EMPTY( Q ) )
		cout<<"����Ϊ��"<<endl ;
	else { 
		temp = Q.front->next ;
		Q.front->next = temp->next ;//��ͷ�ڵ�ָ��ڶ���Ԫ�ؽڵ�
		delete temp ;//ɾ����һ��Ԫ�ؽڵ�
	
		if ( Q.front->next == NULL )//����Ϊ��ʱ��rear��λ
			Q.rear = Q.front ; 
	}
}