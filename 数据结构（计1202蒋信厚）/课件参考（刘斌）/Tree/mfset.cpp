#include "mfset.h"

#ifdef _MFSET_

void Union(int A, int B, MFSET C)
{
	if(C[A].count>C[B].count)
	{
		C[B].father=A;
		C[A].count+=C[B].count;
	}
	else
	{
		C[A].father=B;
		C[B].count+=C[A].count;
	}
}

int Find(int x, MFSET C)
{
	int f;
	f=x;
	while(C[f].father!=0)
		f=C[f].father;
	return f;
}

void Initial(int A, MFSET C)
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
	while(!(i==0 && j==0))
	{
		k=Find(i, S);
		m=Find(j, S);
		if(k!=m)
			Union(k, m, S);
		cin>>i; cin>>j;
	}
}

void print_MFSET(MFSET S)
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

#endif