//�����Ԫ������������Ҷ�ӽ����������Ϊ2�Ľ��ĸ��������Ԫ���߶�
//count2���������⣬����������
#include<iostream>
using namespace std;

//enum BOOLEAN{true,false};

typedef char datatype;
// ����������������ʾ
struct node{
	node *lchild;
	datatype data;
	node *rchild;
};
typedef node *BTREE;

//�ȸ����빹���������Ҷ�ӽ�����������Ϊ#
void createBtree(BTREE &root){
	char ch;
	cout<<"���ȸ������������Ԫ�أ�#��ʾ�գ���"<<endl;
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

//�����ַ�����������������еĸ����//�������أ�����������ͬ
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
//===========================================����������������
void Empty(BTREE BT)//�ÿ�
{
	BT=NULL;
}

bool IsEmpty(BTREE BT )//�ж����Ƿ�Ϊ��
{
	if(BT==NULL)
		return true;
	return false;
}

//�����������������¶�����
BTREE CreateBT(datatype v, BTREE ltree , BTREE rtree )
{
	BTREE root;
	root = new node;
	root ->data = v; 
	root ->lchild = ltree; 
	root ->rchild = rtree;
	return root;
}

BTREE Lchild( BTREE BT )//������
{
	return BT->lchild;
}

BTREE Rchild ( BTREE BT )//������
{
	return BT->rchild;
}


//�ȸ�����
void PreOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
   {
         cout<<BT->data<<" ";
         PreOrder ( Lchild ( BT ) ) ;
         PreOrder( Rchild ( BT ) ) ;
    }
}

//�и�����
void InOrder (BTREE BT )
{ 
    if (!IsEmpty ( BT ) )
    { 
        InOrder ( Lchild ( BT ) ) ;
        cout<<BT->data<<" ";
        InOrder ( Rchild( BT ) ) ;
    }
}

//�������
void PostOrder (BTREE BT )
{ 
    if ( ! IsEmpty ( BT ) )
    { 
        PostOrder( Lchild ( BT ) ) ;        
        PostOrder( Rchild( BT ) ) ;
        cout<<BT->data<<" ";
    }
}

//=============================================�����������㷨��
//����������������ĵݹ��㷨
int countNode( BTREE T )
{
	if ( T == NULL ) 
		return 0;
	else 
		return 1 + countNode ( T->lchild )+ countNode ( T->rchild );
}

//��Ҷ�ӽ��������㷨
int countNodeLeaf(BTREE T)
{ 
	static int LeafNum=0;//Ҷ�ӳ�ʼ��ĿΪ0��ʹ�þ�̬���� 
	if(T)//���ǿ�  
	{     
		if(T->lchild==NULL && T->rchild==NULL)//ΪҶ�ӽ��   
			LeafNum++;//Ҷ����Ŀ��1      
		else//��ΪҶ�ӽ��    
		{         
			countNodeLeaf(T->lchild);//�ݹ�ͳ��������Ҷ����Ŀ      
			countNodeLeaf(T->rchild);//�ݹ�ͳ��������Ҷ����Ŀ    
		} 
	}
	return LeafNum;
}

//���Ϊ2�Ľ��ĸ���

int countNode2(BTREE r)
{ 
	if(r==NULL)	
		return 0;

	else if((r->lchild)&&(r->rchild))//���root��������������
	return 1+countNode2(r->lchild)+countNode2(r->rchild);

	else if(r->lchild)//���rootֻ��������
		return countNode2(r->lchild);

	else //if(r->rchild)//���rootֻ��������
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

//���Ԫ���߶ȵĵݹ��㷨
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

//ɾ����Ԫ���ĵݹ��㷨
void Destroy ( BTREE T )
{
	if ( T != NULL ) 
	{
		Destroy ( T->lchild );
		Destroy ( T->rchild );
		delete T;
	}
}

//�ж����ö������Ƿ�ȼ�
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

//�������ĸ��ƣ����������
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
	createBtree(root,str);//ab##de##cf###,��Ϊ2�Ľ����4��
	cout<<"��������Ϊ2�Ľ�����Ϊ��"<<countNode2(root)<<endl;
	cout<<"Ҷ�ӽڵ����Ϊ��"<<countNodeLeaf(root)<<endl;
	cout<<"���ĸ߶ȣ�"<<Height(root)<<endl;
	cout<<"�и�������"<<endl;
	InOrder(root);
	cout<<endl;
	cout<<"�ȸ�������"<<endl;
	PreOrder(root);
	cout<<endl;
	cout<<"���������"<<endl;
	PostOrder(root);
	cout<<endl;
}


/*
// �и������ķǵݹ��㷨
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
