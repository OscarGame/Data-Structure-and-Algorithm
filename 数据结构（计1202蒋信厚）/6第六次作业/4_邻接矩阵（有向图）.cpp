//邻接矩阵表示：
#include<iostream>
using namespace std;

#define NumVertices 4//顶点数
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
//判断v1是否指向v2
bool IsEdge_directed(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]==0)
			return true;
		else
			return false;
	return false;
}
void NewNode_directed(MTGraph *G, VertexData v)//添加一个顶点，边数不变
{
	G->vexlist[G->n]=v;
	G->n++;
	
}
void DelNode_directed(MTGraph *G, int m)
{
	int i, j;
	if(G->n==0 || m>=NumVertices)
		return;

	for(i=m; i<G->n-1; i++)//删除第m个顶点的位置
		G->vexlist[i]=G->vexlist[i+1];
	for(i=0; i<G->n; i++)//删除与第m个顶点相连的边
	{
		if(G->edge[i][m]!=0)
			G->e--;
	}
	//邻接矩阵降阶
	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n; j++)
			G->edge[i][j]=G->edge[i+1][j];
	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n-1; j++)
			G->edge[j][i]=G->edge[j][i+1];
	G->n--;
}
void SetSucc_directed(MTGraph *G, int v1, int v2, EdgeData w)//v1指向v2
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

void CreateMGraph_directed (MTGraph *G) //创建有向图	
{   
	int i, j, k, w;
	cout<<"输入顶点数和边数:";
	cin>>G->n>>G->e;				

	cout<<"输入顶点的字符:";
	for (i=0; i<G->n; i++) 			
		cin>>G->vexlist[i];
	//初始化邻接矩阵
	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 
		
	for (k=0; k<G->e; k++) {		
		cout<<"输入一条边的两个顶点（先出发点，后终点）以及权值: ";
		cin>>i>>j>>w;				
		G-> edge[i][j]=w;		
	}	
} 
void CreateMGraph_directed(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)//重载创建
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