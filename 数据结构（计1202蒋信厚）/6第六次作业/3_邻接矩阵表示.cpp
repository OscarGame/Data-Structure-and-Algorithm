//�ڽӾ����ʾ��
#include<iostream>
using namespace std;
#define NumVertices 6
typedef char VertexData;//��������
typedef int EdgeData;//����Ȩֵ����

typedef struct{
 VertexData vexlist[NumVertices];
EdgeData edge[NumVertices][NumVertices];//�ڽӾ���
int n;//������
int e;//����
} MTGraph;

void IniMGraph(MTGraph *G)//��ʼ���ڽӱ�
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;
	G->n=0;
	G->e=0;
}

void NewNode(MTGraph *G, VertexData v)//��Ӷ���
{
	G->vexlist[G->n]=v;
	G->n++;
	
}

void DelNode(MTGraph *G, int m)//ɾ������
{
	int i, j;
	if(G->n==0 || m>=NumVertices)//û�ж���||�����ڶ���m
		return;
	for(i=m; i<G->n-1; i++)//����m����Ķ���ǰ��
		G->vexlist[i]=G->vexlist[i+1];

	//ɾ�����m�����������ı�
	//ɾ������
	for(i=0; i<G->n; i++)
	{
		if(G->edge[i][m]!=0)
			G->e--;
	}
	//�ڽӾ��󽵽�
	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n; j++)
			G->edge[i][j]=G->edge[i+1][j];

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n-1; j++)
			G->edge[j][i]=G->edge[j][i+1];
    //����������
	G->n--;
}
//�ж�v1��v2֮����û�б�
bool IsEdge(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]!=0)
			return true;
		else
			return false;
	return false;
}
//�ڶ���v1��v2֮�佨��һ����
void SetSucc(MTGraph *G, int v1, int v2, EdgeData w)
{	
	if(!IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=w;	
		G->edge[v2][v1]=w;
		G->e++;
	}	
}

//ɾ��v1��v2֮��ı�
void DelSucc(MTGraph *G, int v1, int v2)
{
	if(IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=0;
		G->edge[v2][v1]=0;
		G->e--;
	}	
}

//��������ͼ
void CreateMGraph (MTGraph *G) 	
{   
	int i, j, k, w;
	cout<<"���붥�����ͱ���:";
	cin>>G->n>>G->e;				

	cout<<"���붥����ַ�:";
	for (i=0; i<G->n; i++) 			
		cin>>G->vexlist[i];
    //��ʼ���ڽӾ���
	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 
		
	for (k=0; k<G->e; k++) {		
		cout<<"����һ���ߵ���������ͱߵ�Ȩֵ: ";
		cin>>i>>j>>w;			
		G-> edge[i][j]=w;
		G-> edge[j][i]=w;
	}	
}
// 	
void CreateMGraph(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;
	for (i=0; i<n; i++) 			
		G->vexlist[i]=V[i];
	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		
	for(i=0; i<n; i++)				
		for(j=i; j<n; j++)
		{		
			if(E[i][j]!=0)
			{
				G-> edge[i][j]=E[i][j];
				G-> edge[j][i]=E[i][j];
				G->e++;
			}
		}
}
//��ʾ����ͼ
void PrintMT(MTGraph *G)
{
	cout<<'\t';
	//�������
	for(int i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';
	}
	cout<<endl;
	//���ÿ����������ӹ�ϵ
	for(i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';	
		for(int j=0; j<G->n; j++)
			cout<<G->edge[i][j]<<'\t';
		cout<<endl;
	}
}

void main()
{
	/*
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={'v1', 'v2', 'v3', 'v4', 'v5','v6'};
	EdgeData e[6][NumVertices]={
								{0, 1, 0, 1, 0, 1},
								{1, 0, 1, 1, 1, 0},
								{0, 1, 0, 0, 1, 0},
								{1, 1, 0, 0, 1, 1},
								{0, 1, 1, 1, 0, 0},
								{1, 0, 0, 1, 0, 0}
	}                                                                                                                         {1, 0, 0, 1, 0, 0}};
	CreateMGraph(&G, v, e, 6);
	NewNode(&G, 'v1');
	NewNode(&G, 'v2');
	NewNode(&G, 'v3');
	NewNode(&G, 'v4');
	NewNode(&G, 'v5');
	NewNode(&G, 'v6');

	SetSucc(&G, 0, 1, 1);
	SetSucc(&G, 0, 3, 1);
	SetSucc(&G, 1, 3, 1);
	SetSucc(&G, 1, 2, 1);
	SetSucc(&G, 2, 3, 1);
	PrintMT(&G);
	cout<<endl;
	DelSucc(&G, 1, 3);
	PrintMT(&G);
	cout<<endl;
	DelNode(&G, 2);
	*/
}