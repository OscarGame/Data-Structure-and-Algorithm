//没有尾指针的队列，但有一个计数器，所以尾指针rear可以用头指针表示出来
//其中数组表示的队列front指向第一个元素
#include<iostream>
using namespace std;

#define maxlength 20
typedef int elementtype;

struct QUEUE
{
    elementtype elements[maxlength];
    int front;
    int count;//元素个数计数器：rear=(front+count-1)%maxlength
};

int addone( int i )//指针后移
{
	return ((i+1)%maxlength);
}

bool isEmpty(QUEUE Q)//队列是否为空
{
	if (Q.count==0)
		return true ;
	else
		return false ;
}

bool isFull(QUEUE Q)//队列是否已满
{
    if (Q.count==maxlength)
        return true;
    else
        return false;
}

elementtype front(QUEUE Q)//返回队头元素，front指向的元素
{
	if (isEmpty(Q))
		return NULL ;
	else
		return(Q.elements[Q.front]);
}

void enQueue(elementtype x,QUEUE &Q)//队列后插入一个元素，入队
{
	if (isFull(Q))
		cout<<"队列已满"<<endl;
	else
    {
		Q.count++;
		Q.elements[(Q.front+Q.count-1)%maxlength]=x;
	}
}

void deQueue (QUEUE &Q)//删除队头元素,出队
{
	if(isEmpty(Q))
		cout<<"队列为空";
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
	cout<<"队头："<<front(Q)<<endl;
    print(Q);
    for (i=0; i<6; i++)
		deQueue(Q);
	cout<<"删除前六个元素后的队列："<<endl;
        print(Q);
}