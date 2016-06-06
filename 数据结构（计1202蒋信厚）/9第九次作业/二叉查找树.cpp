#include<iostream>
using namespace std;

typedef int records;
//二叉查找树节点类型
struct celltype{
	records data;
	celltype *rchild,*lchild;
};

typedef celltype *BST;

//在F所指的二叉查找树中插入新记录R
void insert(records R,  BST &F)
{
	if(F == NULL)
	{
		F=new celltype;
		F->data = R;
		F->lchild = NULL;
		F->rchild = NULL;
	}
	else if(R<F->data)
		insert(R,F->lchild);
	else if(R>F->data)
		insert(R,F->rchild);
	else return;
}

void create(BST &F)
{
	int input;
	cout<<"请输入二叉树插入序列，输入-1结束："<<endl;
	while(input!=-1)
	{
		insert(input,F);
		cin>>input;
	}
}
//中根遍历二叉查找树
void inOrder(BST F)
{
	if(F!=NULL)
	{
	inOrder(F->lchild);
	cout<<F->data<<'\t';
	inOrder(F->rchild);
	}
}
//判断F是不是二叉排序树
void isBST(BST F,bool &is)
{
	if(F->lchild && F->rchild)//左右子树都不为空
	{
	if(F->data>F->lchild->data && F->data<F->rchild->data)
	{
			 isBST(F->lchild,is);
			 isBST(F->rchild,is);
	}
	else
		is=false;
	}
	else if(F->lchild && !F->rchild)//左子树不为空，右子树为空
	{
		if(F->data>F->lchild->data)
			 isBST(F->lchild,is);
		else
			is = false;
	}
	else  if(!F->lchild && F->rchild)//左子树为空，右子树不为空
	{
		if(F->data<F->rchild->data)
			 isBST(F->rchild,is);
		else
			is = false;
	}
}
void main()
{
	cout<<"建立空二叉查找树F："<<endl;
	BST F=NULL;
/*
	cout<<"插入记录：30"<<endl;
	insert(30,F);
	cout<<"插入记录：15"<<endl;
	insert(15,F);
	cout<<"插入记录：28"<<endl;
	insert(28,F);
	cout<<"插入记录：20"<<endl;
	insert(20,F);
	cout<<"插入记录：24"<<endl;
	insert(24,F);
	cout<<"插入记录：10"<<endl;
	insert(10,F);
	cout<<"插入记录：12"<<endl;
	insert(12,F);
	cout<<"插入记录：68"<<endl;
	insert(68,F);
	cout<<"插入记录：35"<<endl;
	insert(35,F);
	cout<<"插入记录：50"<<endl;
	insert(50,F);
	cout<<"插入记录：46"<<endl;
	insert(46,F);
	cout<<"插入记录：55"<<endl;
	insert(55,F);
*/
	create(F);
	cout<<"中根遍历二叉查找树："<<endl;
	inOrder(F);
	cout<<endl;

	bool is=true;
	isBST(F,is);
	if(is)
		cout<<"F是二叉排序树!"<<endl;
	else
		cout<<"F不是二叉排序树!"<<endl;
}