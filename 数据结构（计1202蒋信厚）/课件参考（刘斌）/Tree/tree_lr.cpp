#include "tree_lr.h"

#ifdef _TREE_LR_

void visit(datatype_lr d)
{
	cout<<d;
}

datatype_lr Data(int n)
{
	return cellspace_lr[n].data;
}

// 初始化树
void ini_TREE_LR()
{
	avail=1;
	for(int i=1; i<maxnodes_lr-1; i++)
	{
		cellspace_lr[i].rightsibling=i+1;
		cellspace_lr[i].leftchild=0;
	}
	cellspace_lr[maxnodes_lr-1].rightsibling=0;
}

// 返回根结点
int root_LR()
{
	for(int i=1; i<maxnodes_lr; i++)
		if(cellspace_lr[i].leftchild!=0 && cellspace_lr[i].parent==0)
			return i;
	return 0;
}

// 创建一棵树
int Create_TREE_LR(datatype_lr v, int L, int R)
{   
	int temp=avail, r;
	if(avail==0)
		return 0;	
	avail=cellspace_lr[avail].rightsibling;
	cellspace_lr[temp].leftchild=L;
	cellspace_lr[temp].data=v;
	cellspace_lr[temp].rightsibling=R;
	if(L!=0)
	{
		//cellspace_lr[L].rightsibling=R;
		cellspace_lr[L].parent=temp;
		r=cellspace_lr[L].rightsibling;
		while(r!=0)
		{
			cellspace_lr[r].parent=temp;
			r=cellspace_lr[r].rightsibling;
		}
	}

	//cellspace_lr[R].rightsibling=0;
	return temp;
}

int LeftMostChild(int n)
{
	return cellspace_lr[n].leftchild;
}

int RightSibling(int n)
{
	return cellspace_lr[n].rightsibling;
}

void PreOrder(int n)
{
	int c;
	visit(Data(n));
	c=LeftMostChild(n);
	while(c!=0)
	{
		PreOrder(c);
		c=RightSibling( c);
	}
}

void print_LR()
{
	cout<<" "<<'\t'<<"left"<<'\t'<<"data"<<'\t'<<"par"<<'\t'<<"right"<<endl;
	for(int i=1; i<maxnodes_lr; i++)
	{
		cout<<i<<'\t'<<cellspace_lr[i].leftchild<<'\t'<<cellspace_lr[i].data<<'\t'<<cellspace_lr[i].parent<<'\t'<<cellspace_lr[i].rightsibling<<'\t'<<endl;
	}
}

void main()
{
	int t1, t2, t3;
	ini_TREE_LR();
	
	t1=Create_TREE_LR('d', 0, 0);
	t2=Create_TREE_LR('e', 0, 0);
	t3=Create_TREE_LR('c', t1, t2);
	t1=Create_TREE_LR('b', 0, t3);
	t2=Create_TREE_LR('a', t1, 0);
	
	print_LR();

	PreOrder(root_LR());
	cout<<endl;
	
}


#endif