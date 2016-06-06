//队列的指针实现
#include<iostream>
using namespace std;

#define maxlength 20
typedef int que_elementtype;//队列元素类型

//队列元素节点类型
struct celltype {
	que_elementtype element;
	celltype *next;
};
//队列结构型
struct QUEUE {
	celltype *front;
	celltype *rear;
};
//front指向头结点，rear指向最后一个元素，当rear也指向头结点时队列为空

/*
函数声明
void error(char *str);
void MAKENULL( QUEUE &Q );
BOOLEAN EMPTY( QUEUE &Q );
celltype *FRONT(QUEUE Q);
void ENQUEUE ( que_elementtype x, QUEUE &Q );
void DEQUEUE ( QUEUE &Q );
*/

//队列基本操作
void MAKENULL( QUEUE &Q )
{
	Q.front = new celltype ;
	Q.front->next = NULL ;
	Q.rear = Q.front ;//队列为空
}

bool EMPTY( QUEUE &Q )//判断是否为空
{ 
	if ( Q.front == Q.rear )
		return true ;
	else
		return false ;
}

celltype *FRONT(QUEUE Q)//返回第一个元素节点
{
	if(Q.front==Q.rear)
		return NULL;
	else
		return Q.front->next;
}

void ENQUEUE ( que_elementtype x, QUEUE &Q )//将x插入队尾
{ 
	Q.rear->next = new celltype ;
	Q.rear = Q.rear->next ;
	Q.rear->element = x ;
	Q.rear->next = NULL ;
}

void DEQUEUE ( QUEUE &Q )//删除队列的第一个元素
{ 
	celltype *temp ;//临时元素节点
	if ( EMPTY( Q ) )
		cout<<"队列为空"<<endl ;
	else { 
		temp = Q.front->next ;
		Q.front->next = temp->next ;//表头节点指向第二个元素节点
		delete temp ;//删掉第一个元素节点
	
		if ( Q.front->next == NULL )//队列为空时将rear复位
			Q.rear = Q.front ; 
	}
}