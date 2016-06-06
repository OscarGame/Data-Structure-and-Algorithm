//稀疏矩阵的十字链表表示
#include<iostream>
using namespace std;
typedef int valuetype;//元素值的类型
#define length 4//矩阵的阶

struct node{
	node *LEFT;//左指针域
	node *UP;//右指针域
	int ROW;//行
	int COL;//列
	valuetype VAL;//值
};

node *BASEROW=new node[length];//行表头结点数组
node *BASECOL=new node[length];//列表头结点数组

void init(node BASEROW[],node BASECOL[])//初始化表头结点数组
{
	for(int i=0;i<4;i++)
	{
		BASEROW[i].COL=-1;
		BASEROW[i].LEFT=NULL;

		BASECOL[i].ROW=-1;
		BASECOL[i].UP=NULL;            
	}
}

void create()//用户创建十字链表稀疏矩阵
{
	while(1)
	{
		node *temp=new node;
		cout<<"请按行优先输入稀疏矩阵非零元素的行、列、值（输入-1,-1,-1结束）："<<endl;
		int r,c,v;
		cin>>r>>c>>v;
		if(r==-1) break;
		temp->ROW=r;
		temp->COL=c;
		temp->VAL=v;

		//横向LEFT指针链接
		if(!BASEROW[r].LEFT){//表头结点为空时
			BASEROW[r].LEFT=temp;
			temp->LEFT= &BASEROW[r];
		}
		else{
			temp->LEFT=BASEROW[r].LEFT;
			BASEROW[r].LEFT=temp;
		}

		//纵向UP指针链接
		if(!BASECOL[c].UP){
			BASECOL[c].UP=temp;
			temp->UP= &BASECOL[c];
		}
		else{
			temp->UP=BASECOL[c].UP;
			BASECOL[c].UP=temp;
		}
	}
}//temp什么时候被释放掉了？
void print()//输出十字链表表示的数组
{
	int array[length][length];//数组存储十字链表中保存的数组信息
	//初始化数组
	for(int i=0;i<length;i++)
		for(int j=0;j<length;j++)
			array[i][j]=0;

	node *p=NULL;
	for(i=0;i<length;i++)
	{
		p=BASEROW[i].LEFT;
		while(p->COL!=-1)
		{
			int r=p->ROW;
			int c=p->COL;
			array[r][c]=p->VAL;//p->VAL为什么没有值了？
			p=p->LEFT;
		}
	}

	for(i=0;i<length;i++)
	{
		for(int j=0;j<length;j++)
			cout<<array[i][j]<<'\t';
		cout<<endl;
	}
		
}

void main()
{
	init(BASEROW,BASECOL);
	create();
	print();
}