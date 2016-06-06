#include<iostream.h>
#define n 8  // Ҷ����
#define m 2*(n)-1   // �������

typedef struct{
	double weight;   // Ȩֵ
	int lchild;
	int rchild;
	int parent;
}HTNODE;

typedef HTNODE HuffmanT[m];  // ���������ľ�̬���������ʾ

void InitHT(HuffmanT T)
{
	for(int i=0; i<m; i++)
	{
		T[i].lchild=-1;
		T[i].rchild=-1;
		T[i].parent=-1;
	}
	for(i=0; i<n; i++)
		cin>>T[i].weight;
}
//ѡȡ������С��Ȩֵ
void SelectMin(HuffmanT T, int n1, int &p1, int &p2)
{
	int i, j;
	for(i=0; i<n1; i++)
		if(T[i].parent==-1)
		{
			p1=i;
			break;
		}
	for(j=i+1; j<n1;j++)
		if(T[j].parent==-1)
		{
			p2=j;
			break;
		}
	for(i=0; i<n1; i++)
		if((T[p1].weight>T[i].weight) && (T[i].parent==-1) && (p2!=i))
			p1=i;
	for(i=0; i<n1; i++)
		if((T[p2].weight>T[i].weight) && (T[i].parent==-1) && (p1!=i))
			p2=i;

}
//���������Ľ���
void CreatHT(HuffmanT T)
{
	int i, p1, p2;
	InitHT(T);
	for(i=n; i<m; i++)
	{
		SelectMin(T, i, p1, p2);
		T[p1].parent=T[p2].parent=i;
		T[i].lchild=p1;
		T[i].rchild=p2;
		T[i].weight=T[p1].weight+T[p2].weight;
	}
}

void printHT(HuffmanT T)
{
	for(int i=0; i<m; i++)
	{
		cout<<T[i].weight<<'\t'<<T[i].parent<<'\t'<<T[i].rchild<<'\t'<<T[i].lchild<<endl;
	}
}

void main()
{
	HuffmanT T;
	CreatHT(T);
	printHT(T);
}
//����Ҷ�ӽڵ㼯�ϣ�15, 3,14, 2, 6, 9, 16, 17
