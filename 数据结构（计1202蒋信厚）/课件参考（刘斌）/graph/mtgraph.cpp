#include "index.h"
#include "mtgraph.h"

#ifdef _MTGRAPH_

//无向图
void IniMGraph(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;
	G->n=0;
	G->e=0;
}

void NewNode(MTGraph *G, VertexData v)
{
	G->vexlist[G->n]=v;
	G->n++;
	
}

void DelNode(MTGraph *G, int m)
{
	int i, j;
	if(G->n==0 || m>=NumVertices)
		return;

	for(i=m; i<G->n-1; i++)
		G->vexlist[i]=G->vexlist[i+1];

	for(i=0; i<G->n; i++)
	{
		if(G->edge[i][m]!=0)
			G->e--;
	}

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n; j++)
			G->edge[i][j]=G->edge[i+1][j];

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n-1; j++)
			G->edge[j][i]=G->edge[j][i+1];

	G->n--;
}

void SetSucc(MTGraph *G, int v1, int v2, EdgeData w)
{	
	if(!IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=w;	
		G->edge[v2][v1]=w;
		G->e++;
	}	
}

void DelSucc(MTGraph *G, int v1, int v2)
{
	if(IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=0;
		G->edge[v2][v1]=0;
		G->e--;
	}	
}

BOOLEAN IsEdge(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]!=0)
			return TRUE;
		else
			return FALSE;
	return FALSE;
}

void CreateMGraph (MTGraph *G) 	//建立(无向)图的邻接矩阵
{   
	int i, j, k, w;
	cout<<"输入顶点数和边数:";
	cin>>G->n>>G->e;				//1.输入顶点数和边数

	cout<<"输入顶点的字符:";
	for (i=0; i<G->n; i++) 			//2.读入顶点信息，建立顶点表
		cin>>G->vexlist[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		//3.邻接矩阵初始化

	
	for (k=0; k<G->e; k++) {		//4.读入e条边建立邻接矩阵
		cout<<"输入一条边的两个顶点: ";
		cin>>i>>j>>w;				//输入边（i,j）上的权w
		G-> edge[i][j]=w;
		G-> edge[j][i]=w;
	}	//空间复杂性：S= O( n+n2 )
} 	//时间复杂性：T=O(n+ n2 +e) 。当e < n, T= O( n2 )

void CreateMGraph(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;

	for (i=0; i<n; i++) 			//2.读入顶点信息，建立顶点表
		G->vexlist[i]=V[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		//3.邻接矩阵初始化
	
	for(i=0; i<n; i++)				//4.读入e条边建立邻接矩阵
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

// 有向图
void IniMGraph_directed(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=MaxValue;
	G->n=0;
	G->e=0;
}

void NewNode_directed(MTGraph *G, VertexData v)
{
	G->vexlist[G->n]=v;
	G->n++;
	
}

void DelNode_directed(MTGraph *G, int m)
{
	int i, j;
	if(G->n==0 || m>=NumVertices)
		return;

	for(i=m; i<G->n-1; i++)
		G->vexlist[i]=G->vexlist[i+1];

	for(i=0; i<G->n; i++)
	{
		if(G->edge[i][m]!=MaxValue)
			G->e--;
	}

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n; j++)
			G->edge[i][j]=G->edge[i+1][j];

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n-1; j++)
			G->edge[j][i]=G->edge[j][i+1];

	G->n--;
}

void SetSucc_directed(MTGraph *G, int v1, int v2, EdgeData w)
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
		G->edge[v1][v2]=MaxValue;		
		G->e--;
	}	
}

BOOLEAN IsEdge_directed(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]!=MaxValue)
			return TRUE;
		else
			return FALSE;
	return FALSE;
}

void CreateMGraph_directed (MTGraph *G) 	//建立图的邻接矩阵
{   
	int i, j, k, w;
	cout<<"输入顶点数和边数:";
	cin>>G->n>>G->e;				//1.输入顶点数和边数

	cout<<"输入顶点的字符:";
	for (i=0; i<G->n; i++) 			//2.读入顶点信息，建立顶点表
		cin>>G->vexlist[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		//3.邻接矩阵初始化

	
	for (k=0; k<G->e; k++) {		//4.读入e条边建立邻接矩阵
		cout<<"输入一条边的两个顶点: ";
		cin>>i>>j>>w;				//输入边（i,j）上的权w
		G-> edge[i][j]=w;		
	}	//空间复杂性：S= O( n+n2 )
} 	//时间复杂性：T=O(n+ n2 +e) 。当e < n, T= O( n2 )

void CreateMGraph_directed(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;

	for (i=0; i<n; i++) 			//2.读入顶点信息，建立顶点表
		G->vexlist[i]=V[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=MaxValue; 		//3.邻接矩阵初始化
	
	for(i=0; i<n; i++)				//4.读入e条边建立邻接矩阵
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

#ifndef _DFS_
#ifndef _BFS_
#ifndef _PRIME_
#ifndef _KRUSKAL_
#ifndef _DIJKSTRA_
#ifndef _FLOYD_

void main()
{
	MTGraph G;

	// 无向图
	
	/*IniMGraph(&G);
	
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={
								{0, 1, 0, 1, 1},
								{1, 0, 1, 0, 0},
								{0, 1, 0, 0, 1},
								{1, 0, 0, 0, 1},
								{1, 0, 1, 1, 0}};
	CreateMGraph(&G, v, e, 5);*/

	//CreateMGraph(&G);
/*
	NewNode(&G, 'a');
	NewNode(&G, 'b');
	NewNode(&G, 'c');
	NewNode(&G, 'd');

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

	DelNode(&G, 2);*/

	//有向图
	IniMGraph_directed(&G);
	
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={
								{MaxValue,       10, MaxValue,       30,      100},
								{MaxValue, MaxValue,       50, MaxValue, MaxValue},
								{MaxValue, MaxValue, MaxValue,       20,       10},
								{MaxValue, MaxValue,       20, MaxValue,       60},
								{MaxValue, MaxValue, MaxValue, MaxValue, MaxValue}};
	CreateMGraph_directed(&G, v, e, 5);

	PrintMT(&G);
	cout<<endl;
}
#endif
#endif
#endif
#endif
#endif
#endif
#endif