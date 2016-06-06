//�ڽӾ����ʾ��
#include<iostream>
using namespace std;

#define NumVertices 4//������
typedef char VertexData; 		
typedef int EdgeData;
			
typedef struct{
    VertexData vexlist[NumVertices]; 	
    EdgeData edge[NumVertices][NumVertices];
    int n;			
	int e; 		
} MTGraph;
void IniMGraph_directed(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;
	G->n=0;
	G->e=0;
}
//�ж�v1�Ƿ�ָ��v2
bool IsEdge_directed(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]==0)
			return true;
		else
			return false;
	return false;
}
void NewNode_directed(MTGraph *G, VertexData v)//���һ�����㣬��������
{
	G->vexlist[G->n]=v;
	G->n++;
	
}
void DelNode_directed(MTGraph *G, int m)
{
	int i, j;
	if(G->n==0 || m>=NumVertices)
		return;

	for(i=m; i<G->n-1; i++)//ɾ����m�������λ��
		G->vexlist[i]=G->vexlist[i+1];
	for(i=0; i<G->n; i++)//ɾ�����m�����������ı�
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
	G->n--;
}
void SetSucc_directed(MTGraph *G, int v1, int v2, EdgeData w)//v1ָ��v2
{	
	if(!IsEdge_directed(G, v1, v2))
	{
		G->edge[v1][v2]=w;		
		G->e++;
	}	
}
void DelSucc_directed(MTGraph *G, int v1, int v2)
{
	if(IsEdge_directed(G, v1, v2))
	{
		G->edge[v1][v2]=0;		
		G->e--;
	}	
}

void CreateMGraph_directed (MTGraph *G) //��������ͼ	
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
		cout<<"����һ���ߵ��������㣨�ȳ����㣬���յ㣩�Լ�Ȩֵ: ";
		cin>>i>>j>>w;				
		G-> edge[i][j]=w;		
	}	
} 
void CreateMGraph_directed(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)//���ش���
{
	int i, j;	
	G->n=n;
	for (i=0; i<n; i++) 			
		G->vexlist[i]=V[i];
	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 			
	for(i=0; i<n; i++)				
		for(j=0; j<n; j++)
		{		
			if(E[i][j]!=0)
			{
				G-> edge[i][j]=E[i][j];			
				G->e++;
			}
		}
}
void PrintMT(MTGraph *G)
{
	cout<<'\t';
	for(int i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';
	}
	cout<<endl;
	for(i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';	
		for(int j=0; j<G->n; j++)
			cout<<G->edge[i][j]<<'\t';
		cout<<endl;
	}
}
void main()
{/*
	MTGraph G;
		IniMGraph_directed(&G);	
	VertexData v[4]={'v1', 'v2', 'v3', 'v4'};
	EdgeData e[4][NumVertices]={
								{0,1,1,0},
								{0,0,0,0},
								{0,0,0,1},
								{1,0,0,0}};
	CreateMGraph_directed(&G, v, e, 4);
	PrintMT(&G);
	cout<<endl;
	*/
}