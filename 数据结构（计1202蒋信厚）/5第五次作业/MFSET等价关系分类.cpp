#include<iostream.h>
#define n 10//MEFSETԪ�ظ���

//MFSET����������
struct mfnode{
	int father;//ָ�򸸽ڵ����
	int count;//��������
};

typedef mfnode MFSET[n+1];

void Union(int A, int B, MFSET C)//�ϲ�A��B
{
	if(C[A].count>C[B].count)
	{
		C[B].father=A;//B����A
		C[A].count+=C[B].count;
	}
	else
	{
		C[A].father=B;//A����B
		C[B].count+=C[A].count;
	}
}

int Find(int x, MFSET C)//�����Ԫ��x�����ĸ�
{
	int f;
	f=x;
	while(C[f].father!=0)//δ����
		f=C[f].father;
	return f;
}

void Initial(int A, MFSET C)//����Aֻ����Ԫ��A
{
	C[A].father=0;
	C[A].count=1;
}

// �ȼ۷���
void Equivalence(MFSET S)
{
	int i, j, m, k;
	for(i=1; i<=n; i++)
		Initial(i, S);
	cin>>i; cin>>j;
	while(!(i==0 && j==0))//����0,0�����ȼ۷���
	{
		k=Find(i, S);
		m=Find(j, S);
		if(k!=m)
			Union(k, m, S);
		cin>>i; cin>>j;
	}
}

void print_MFSET(MFSET S)//����ȼ���
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
