#include<iostream>
using namespace std;

struct node
{
	int father;//指向父节点的链
	int count;//树结点个数
};

typedef node MFSET[101];//比结点个数大一
//归并，将节点个数相对较小的树归并到结点个数较多的树下
void Union(int A,int B,MFSET a)
{
	if(a[A].count>a[B].count)
	{
		a[B].father=A;
		a[A].count=a[A].count+a[B].count;
	}
	else
	{
		a[A].father=B;
		a[B].count=a[A].count+a[B].count;
	}
}

int Find(int x,MFSET a)//返回根节点，根结点的父亲为0
{
	while(a[x].father!=0)
	{
		x=a[x].father;
	}
	return x;
}

void Initial(int A,MFSET a)//构造等价类。
{
	a[A].father=0;
	a[A].count=1;
}

//等价分类函数
void Equivalence(MFSET a,int y)//y是该集合的总个数
{
	int m,n;
	for(int i=1;i<y+1;i++)
		Initial(i,a);//初始化
	while(1)
	{
		cout<<"请输入等价类(输入0表示等价关系输入完毕)"<<endl;
		cin>>n;
		if(n==0)
			break;
		cin>>m;
		n=Find(n,a);
		m=Find(m,a);
		if(m!=n)
			Union(n,m,a);//归并等价类
	}

}
//输出等价类的根
void Showup(MFSET a)
{
	int i=1;
	while(1)
	{
		if(a[i].father!=0)
		{
			cout<<Find(i,a)<<endl;
		}
		i++;
		if(i>9)
			break;
		if(a[i].father==0)
			cout<<i<<endl;
	}
}
int main()
{
	MFSET a;
	Equivalence(a,9);// 1≡5、6≡8、7≡2、9≡8、3≡7、4≡2、9≡3
	Showup(a);
	return 0;
}