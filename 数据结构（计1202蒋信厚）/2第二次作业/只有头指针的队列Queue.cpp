//û��βָ��Ķ��У�����һ��������������βָ��rear������ͷָ���ʾ����
//���������ʾ�Ķ���frontָ���һ��Ԫ��
#include<iostream>
using namespace std;

#define maxlength 20
typedef int elementtype;

struct QUEUE
{
    elementtype elements[maxlength];
    int front;
    int count;//Ԫ�ظ�����������rear=(front+count-1)%maxlength
};

int addone( int i )//ָ�����
{
	return ((i+1)%maxlength);
}

bool isEmpty(QUEUE Q)//�����Ƿ�Ϊ��
{
	if (Q.count==0)
		return true ;
	else
		return false ;
}

bool isFull(QUEUE Q)//�����Ƿ�����
{
    if (Q.count==maxlength)
        return true;
    else
        return false;
}

elementtype front(QUEUE Q)//���ض�ͷԪ�أ�frontָ���Ԫ��
{
	if (isEmpty(Q))
		return NULL ;
	else
		return(Q.elements[Q.front]);
}

void enQueue(elementtype x,QUEUE &Q)//���к����һ��Ԫ�أ����
{
	if (isFull(Q))
		cout<<"��������"<<endl;
	else
    {
		Q.count++;
		Q.elements[(Q.front+Q.count-1)%maxlength]=x;
	}
}

void deQueue (QUEUE &Q)//ɾ����ͷԪ��,����
{
	if(isEmpty(Q))
		cout<<"����Ϊ��";
	else
    {
		Q.front=addone(Q.front);
        Q.count--;
    }
}

void print(QUEUE Q)
{
    for (int j=0;j<Q.count;j++)
        cout<<Q.elements[(Q.front+j)%maxlength]<<"\t";
	cout<<endl;
}

void main()
{
    QUEUE Q;
    Q.front=0;
    Q.count=0;
    for (int i=1; i<10; i++)
        enQueue(i, Q);
	cout<<"��ͷ��"<<front(Q)<<endl;
    print(Q);
    for (i=0; i<6; i++)
		deQueue(Q);
	cout<<"ɾ��ǰ����Ԫ�غ�Ķ��У�"<<endl;
        print(Q);
}