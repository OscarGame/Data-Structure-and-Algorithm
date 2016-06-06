#include<iostream>
using namespace std;

typedef int records;
//����������ڵ�����
struct celltype{
	records data;
	celltype *rchild,*lchild;
};

typedef celltype *BST;

//��F��ָ�Ķ���������в����¼�¼R
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
	cout<<"������������������У�����-1������"<<endl;
	while(input!=-1)
	{
		insert(input,F);
		cin>>input;
	}
}
//�и��������������
void inOrder(BST F)
{
	if(F!=NULL)
	{
	inOrder(F->lchild);
	cout<<F->data<<'\t';
	inOrder(F->rchild);
	}
}
//�ж�F�ǲ��Ƕ���������
void isBST(BST F,bool &is)
{
	if(F->lchild && F->rchild)//������������Ϊ��
	{
	if(F->data>F->lchild->data && F->data<F->rchild->data)
	{
			 isBST(F->lchild,is);
			 isBST(F->rchild,is);
	}
	else
		is=false;
	}
	else if(F->lchild && !F->rchild)//��������Ϊ�գ�������Ϊ��
	{
		if(F->data>F->lchild->data)
			 isBST(F->lchild,is);
		else
			is = false;
	}
	else  if(!F->lchild && F->rchild)//������Ϊ�գ���������Ϊ��
	{
		if(F->data<F->rchild->data)
			 isBST(F->rchild,is);
		else
			is = false;
	}
}
void main()
{
	cout<<"�����ն��������F��"<<endl;
	BST F=NULL;
/*
	cout<<"�����¼��30"<<endl;
	insert(30,F);
	cout<<"�����¼��15"<<endl;
	insert(15,F);
	cout<<"�����¼��28"<<endl;
	insert(28,F);
	cout<<"�����¼��20"<<endl;
	insert(20,F);
	cout<<"�����¼��24"<<endl;
	insert(24,F);
	cout<<"�����¼��10"<<endl;
	insert(10,F);
	cout<<"�����¼��12"<<endl;
	insert(12,F);
	cout<<"�����¼��68"<<endl;
	insert(68,F);
	cout<<"�����¼��35"<<endl;
	insert(35,F);
	cout<<"�����¼��50"<<endl;
	insert(50,F);
	cout<<"�����¼��46"<<endl;
	insert(46,F);
	cout<<"�����¼��55"<<endl;
	insert(55,F);
*/
	create(F);
	cout<<"�и����������������"<<endl;
	inOrder(F);
	cout<<endl;

	bool is=true;
	isBST(F,is);
	if(is)
		cout<<"F�Ƕ���������!"<<endl;
	else
		cout<<"F���Ƕ���������!"<<endl;
}