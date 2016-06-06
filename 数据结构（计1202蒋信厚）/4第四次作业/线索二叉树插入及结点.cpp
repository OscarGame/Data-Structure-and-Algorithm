//中序线索二叉树的左右节点插入操作
#include<iostream.h>
//中序线索二叉树节点类型
 struct node{
	node * lchild;
	node * rchild;
	bool ltag;//左右子树是否存在
	bool rtag;
	char info;
};

 typedef node THTREE;
//求后驱节点
node * Next(node * P)
{
	node * Q = P->rchild;
	if(P->rtag==true)//如果P的右子树存在，则其后驱结点为右子树的最左结点
		while(Q->ltag==true)
			Q=Q->lchild;
		return Q;//右子树的最左子树
}
//求前驱结点
node *Previous(node *P)
{
	node *Q = P->lchild;
	if(P->ltag==true)//如果P的左子树存在，则其前驱结点为左子树的最右结点
		while(Q->rtag==true)
			Q=Q->rchild;
		return Q;//左子树的最右结点
}
//中根遍历线索二叉树
void ThInOrder(THTREE * HEAD)
{
	node * temp = HEAD;
	cout<<"中根遍历线索二叉树为："<<endl;
	do{
		temp=Next(temp);
		if(temp!=HEAD)
			cout<<temp->info<<" ";
	}while(temp!=HEAD);
}
//右插入结点
void RInsert(node * S,node * R)
{
	node * W;
	R->rchild=S->rchild;
	R->rtag=S->rtag;
	R->lchild=S;
	R->ltag=false;

	S->rchild=R;
	S->rtag=true;

	if(R->rtag==true)//如果本来有右子树
	{
		W=Next(R);
		W->lchild=R;//将右边插入的结点R的后驱的左孩子指向R
	}
}
//左插入结点
void LInsert(node * S,node * L)
{
	node * W;
	L->lchild=S->lchild;
	L->ltag=S->ltag;
	L->rtag=false;
	L->rchild=S;

	S->lchild=L;
	S->ltag=true;

	if(L->ltag == true)//如果S本来有左子树
	{
		W = Previous(L);
		W->rchild = L;//将左边插入的结点L的前驱的右孩子指向L
	}
}
/*
//插入左子树???
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
//HEAD为头结点，A为根节点
node * HEAD= new node;//头结点
node * A=new node;//根节点
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

node * B = new node;//左孩子
B->info='B';
node * C = new node;//右孩子
C->info='C';
//构造线索二叉树BAC
LInsert(A,B);
RInsert(A,C);
ThInOrder(HEAD);
cout<<endl;
//在结点A左边插入结点D,右边插入结点E
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