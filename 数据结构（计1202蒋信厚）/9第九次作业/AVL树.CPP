#include<iostream>
using namespace std;

typedef int records;
//AVL树节点类型
struct celltype{
	int bf;//AVL的平衡因子
	records data;
	celltype *rchild,*lchild;
};

typedef celltype *AVL;

void leftRotation(AVL &F,bool &unbalanced)
{
	AVL gc,lc;
	lc = F->lchild;
	if(lc->lchild->bf==1)//LL
	{
		F->lchild = lc->rchild;
        lc->rchild = F;
		F->bf = 0;
		F = lc;
	}
	else//LR
	{
		gc = lc->rchild;
		lc->rchild = gc->lchild;
		gc->lchild = lc;
		F->lchild = gc->rchild;
		gc->rchild = F;
		switch(gc->bf){
		case 1:
			F->bf = -1;
			lc->bf = 0;
			break;
		case 0:
			F->bf=lc->bf = 0;
			break;
		case -1:
			F->bf = 0;
			lc->bf = 1;
		}
		F = gc;
	}
	F->bf = 0;
	unbalanced = false;
}

void rightRotation(AVL &F,bool &unbalanced)
{
	AVL gc,rc;
	rc = F->rchild;
	if(rc->lchild->bf==-1)//RR
	{
		F->rchild = rc->lchild;
        rc->lchild = F;
		F->bf = 0;
		F = rc;
	}
	else//RL
	{
		gc = rc->lchild;
		rc->lchild = gc->rchild;
		gc->rchild = rc;
		F->rchild = gc->lchild;
		gc->lchild = F;
		switch(gc->bf){
		case 1:
			F->bf = 1;
			rc->bf = 0;
			break;
		case 0:
			F->bf=rc->bf = 0;
			break;
		case -1:
			F->bf = 0;
			rc->bf = -1;
		}
		F = gc;
	}
	F->bf = 0;
	unbalanced = false;
}

//在F所指的二叉查找树中插入新记录R
void insert(AVL &F,records R,bool &unbalanced)
{
	if(F == NULL)//向空二叉树中插入新元素  
	{
		unbalanced = true;
		F=new celltype;
		F->data = R;
		F->lchild = NULL;
		F->rchild = NULL;
		F->bf = 0;
	}
	else if(R<F->data)//在左子树上插入
	{
		insert(F->lchild,R,unbalanced);
		if(unbalanced)
			switch(F->bf){
               case -1:F->bf = 0;
				   unbalanced = false;
				   break;
               case 0:F->bf = 1;
				   break;
			   case 1:leftRotation(F,unbalanced);
		}
	}
	else if(R>F->data)//在右子树上插入
	{
		insert(F->rchild,R,unbalanced);
		if(unbalanced)
			switch(F->bf){
               case -1:F->bf = 0;
				   unbalanced = false;
				   break;
               case 0:F->bf = -1;
				   break;
               case 1:rightRotation(F,unbalanced);
		}
	}
	else
		unbalanced = false;
}

//中根遍历二叉查找树
void inOrder(AVL F)
{
	if(F!=NULL)
	{
	inOrder(F->lchild);
	cout<<F->data<<'\t';
	inOrder(F->rchild);
	}
}

//利用平衡因子求二叉树的高度
void height(AVL F,int &h)
{
	if(F){
		++h;
		if(F->bf>0)//如果bf大于0跳到左子树中递归
			height(F->lchild,h);
		else if(F->bf<0)//如果bf小于0跳到右子树中递归
			height(F->rchild,h);
		else if(F->bf == 0 && F->lchild)
			height(F->lchild,h);//或者isBST(F->rchild);
		else
			return;
	}
}
void main()
{
	bool unbalanced =false;
	cout<<"建立空二叉查找树F："<<endl;
	AVL F=NULL;
	cout<<"插入记录：30"<<endl;
	insert(F,30,unbalanced);
	cout<<"插入记录：15"<<endl;
	insert(F,15,unbalanced);
	cout<<"插入记录：28"<<endl;
	insert(F,28,unbalanced);
	cout<<"插入记录：20"<<endl;
	insert(F,20,unbalanced);
	cout<<"插入记录：24"<<endl;
	insert(F,24,unbalanced);
	cout<<"插入记录：10"<<endl;
	insert(F,10,unbalanced);
	cout<<"插入记录：12"<<endl;
	insert(F,12,unbalanced);
	cout<<"插入记录：68"<<endl;
	insert(F,68,unbalanced);
	cout<<"插入记录：35"<<endl;
	insert(F,35,unbalanced);
	cout<<"插入记录：50"<<endl;
	insert(F,50,unbalanced);
	cout<<"插入记录：46"<<endl;
	insert(F,46,unbalanced);
	cout<<"插入记录：55"<<endl;
	insert(F,55,unbalanced);
	cout<<"中根遍历二叉查找树："<<endl;
	inOrder(F);
	cout<<endl;
	int h=0;
	height(F,h);
	cout<<"树的高度为："<<h<<endl;
}