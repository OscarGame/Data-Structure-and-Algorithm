//计算二元树结点个数、求叶子结点个数、求度为2的结点的个数、求二元树高度
//count2函数有问题，遍历有问题
#include<iostream>
using namespace std;

//enum BOOLEAN{true,false};

typedef char datatype;
// 二叉树的左右链表示
struct node{
	node *lchild;
	datatype data;
	node *rchild;
};
typedef node *BTREE;

//先根输入构造二叉树，叶子结点的左右子树为#
void createBtree(BTREE &root){
	char ch;
	cout<<"请先根输入二叉树的元素（#表示空）："<<endl;
	cin>>ch;
	if (ch=='#')
	{	
		root=NULL;
		return;	
	}
	root=new node;
	root->data=ch;
	root->lchild=NULL;
	root->rchild=NULL;
	createBtree(root->lchild);
	createBtree(root->rchild);
}

//利用字符串先序输入二叉树中的各结点//函数重载，参数数量不同
void createBtree(BTREE & T, char *&str)
{ 
	char ch;
	ch=*str++;
	if ( ch == '#' ) 
		T = NULL ;
	else{ 
		T = new node;
		T->data = ch ;
	createBtree ( T -> lchild, str ) ;
	createBtree ( T -> rchild, str ) ;
	}
}
//===========================================二叉树基本操作：
void Empty(BTREE BT)//置空
{
	BT=NULL;
}

bool IsEmpty(BTREE BT )//判断树是否为空
{
	if(BT==NULL)
		return true;
	return false;
}

//利用左右子树建立新二叉树
BTREE CreateBT(datatype v, BTREE ltree , BTREE rtree )
{
	BTREE root;
	root = new node;
	root ->data = v; 
	root ->lchild = ltree; 
	root ->rchild = rtree;
	return root;
}

BTREE Lchild( BTREE BT )//左子树
{
	return BT->lchild;
}

BTREE Rchild ( BTREE BT )//右子树
{
	return BT->rchild;
}


//先根遍历
void PreOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
   {
         cout<<BT->data<<" ";
         PreOrder ( Lchild ( BT ) ) ;
         PreOrder( Rchild ( BT ) ) ;
    }
}

//中根遍历
void InOrder (BTREE BT )
{ 
    if (!IsEmpty ( BT ) )
    { 
        InOrder ( Lchild ( BT ) ) ;
        cout<<BT->data<<" ";
        InOrder ( Rchild( BT ) ) ;
    }
}

//后根遍历
void PostOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
    { 
        PostOrder( Lchild ( BT ) ) ;        
        PostOrder( Rchild( BT ) ) ;
        cout<<BT->data<<" ";
    }
}

//=============================================二叉树操作算法：
//计算二叉树结点个数的递归算法
int countNode( BTREE T )
{
	if ( T == NULL ) 
		return 0;
	else 
		return 1 + countNode ( T->lchild )+ countNode ( T->rchild );
}

//求叶子结点个数的算法
int countNodeLeaf(BTREE T)
{ 
	static int LeafNum=0;//叶子初始数目为0，使用静态变量 
	if(T)//树非空  
	{     
		if(T->lchild==NULL && T->rchild==NULL)//为叶子结点   
			LeafNum++;//叶子数目加1      
		else//不为叶子结点    
		{         
			countNodeLeaf(T->lchild);//递归统计左子树叶子数目      
			countNodeLeaf(T->rchild);//递归统计右子树叶子数目    
		} 
	}
	return LeafNum;
}

//求度为2的结点的个数

int countNode2(BTREE r)
{ 
	if(r==NULL)	
		return 0;

	else if((r->lchild)&&(r->rchild))//如果root左右子树都存在
	return 1+countNode2(r->lchild)+countNode2(r->rchild);

	else if(r->lchild)//如果root只有左子树
		return countNode2(r->lchild);

	else //if(r->rchild)//如果root只有右子树
		return countNode2(r->rchild);
}
/*
int countNode2(BTREE r)
{
	static numNode2 = 0;
	if(r->lchild && r->rchild){
		numNode2++;
		countNode2(r->lchild);
		countNode2(r->rchild);
	}
	else if(r->lchild)
		countNode2(r->lchild);
	else if(r->rchild)
		countNode2(r->rchild);
	return numNode2;
}*/

//求二元树高度的递归算法
int Height (BTREE T )
{ 
	if ( T == NULL ) 
		return 0;
	else 
	{
		int m = Height ( T->lchild );
		int n = Height ( T->rchild ) ;
		return (m > n) ? (m+1) : (n+1);
	}
}

//删除二元树的递归算法
void Destroy ( BTREE T )
{
	if ( T != NULL ) 
	{
		Destroy ( T->lchild );
		Destroy ( T->rchild );
		delete T;
	}
}

//判断两棵二叉树是否等价
int Equal(BTREE firstbt , BTREE secondbt )
{   
	int x = 0;
	if ( IsEmpty(firstbt) && IsEmpty(secondbt) )
		x = 1 ;
	else if ( ! IsEmpty( firstbt ) && ! IsEmpty( secondbt ) )
		if ( firstbt->data == secondbt->data )
		  if ( Equal( Lchild( firstbt ) , Lchild( secondbt ) ) )
			  x= Equal( Rchild( firstbt ) , Rchild( secondbt) );
	return x;
} 

//二叉树的复制，后根遍历法
BTREE CopyBT( BTREE oldtree )
{   
	BTREE temp ;
	if ( oldtree != NULL )
	{   
		temp = new node ;
		temp -> lchild = CopyBT( oldtree->lchild ) ;
		temp -> rchild = CopyBT( oldtree->rchild ) ;
		temp -> data = oldtree->data ;
		return temp;
	}
	return NULL;
} 


void main()
{
	BTREE root=NULL;
	char *str = "ab##de##cf###";
	createBtree(root,str);//ab##de##cf###,度为2的结点有4个
	cout<<"二叉树度为2的结点个数为："<<countNode2(root)<<endl;
	cout<<"叶子节点个数为："<<countNodeLeaf(root)<<endl;
	cout<<"树的高度："<<Height(root)<<endl;
	cout<<"中根遍历："<<endl;
	InOrder(root);
	cout<<endl;
	cout<<"先根遍历："<<endl;
	PreOrder(root);
	cout<<endl;
	cout<<"后根遍历："<<endl;
	PostOrder(root);
	cout<<endl;
}


/*
// 中根遍历的非递归算法
void NInOrder(BTREE  BT )
{    
	STACK S ; 
	BTREE T=BT ;
	MakeNull( S ) ;
	while ( !IsEmpty( T ) || Empty ( S ) )
		if ( !IsEmpty ( T ) )
		{    
			Push( T ,S );
			T =  Lchild ( T ) ; 
		}
		else
		{    
			T = Top ( S ); 
			Pop ( S ) ;
			visit( Data( T ) ) ;
			T = Rchild ( T ) ; 
		}
}
*/
