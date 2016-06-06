#include<iostream.h>
#define n 10//MEFSET元素个数

//MFSET抽象数据型
struct mfnode{
	int father;//指向父节点的链
	int count;//树结点个数
};

typedef mfnode MFSET[n+1];

void Union(int A, int B, MFSET C)//合并A和B
{
	if(C[A].count>C[B].count)
	{
		C[B].father=A;//B并入A
		C[A].count+=C[B].count;
	}
	else
	{
		C[A].father=B;//A并入B
		C[B].count+=C[A].count;
	}
}

int Find(int x, MFSET C)//求包含元素x的树的根
{
	int f;
	f=x;
	while(C[f].father!=0)//未到根
		f=C[f].father;
	return f;
}

void Initial(int A, MFSET C)//集合A只包含元素A
{
	C[A].father=0;
	C[A].count=1;
}

// 等价分类
void Equivalence(MFSET S)
{
	int i, j, m, k;
	for(i=1; i<=n; i++)
		Initial(i, S);
	cin>>i; cin>>j;
	while(!(i==0 && j==0))//输入0,0结束等价分类
	{
		k=Find(i, S);
		m=Find(j, S);
		if(k!=m)
			Union(k, m, S);
		cin>>i; cin>>j;
	}
}

void print_MFSET(MFSET S)//输出等价类
{
	int r[n+1][n+1]={0}, k;
	for(int i=1; i<=n; i++)
	{
		k=Find(i, S);
		r[k][0]++;
		r[k][r[k][0]]=i;
	}
	for(i=1; i<=n; i++)
	{
		if(r[i][0]>0)
		{
			cout<<'{';
			for(int j=1; j<r[i][0]; j++)
				cout<<r[i][j]<<',';
			cout<<r[i][r[i][0]]<<'}'<<endl;
		}
	}
}

void main()
{
	MFSET S;
	Equivalence(S);
	print_MFSET(S);
}
