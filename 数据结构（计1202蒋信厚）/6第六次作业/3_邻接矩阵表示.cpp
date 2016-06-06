//邻接矩阵表示：
#include<iostream>
using namespace std;
#define NumVertices 6
typedef char VertexData;//顶点类型
typedef int EdgeData;//边上权值类型

typedef struct{
 VertexData vexlist[NumVertices];
EdgeData edge[NumVertices][NumVertices];//邻接矩阵
int n;//定点数
int e;//边数
} MTGraph;

void IniMGraph(MTGraph *G)//初始化邻接表
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;
	G->n=0;
	G->e=0;
}

void NewNode(MTGraph *G, VertexData v)//添加顶点
{
	G->vexlist[G->n]=v;
	G->n++;
	
}

void DelNode(MTGraph *G, int m)//删除顶点
{
	int i, j;
	if(G->n==0 || m>=NumVertices)//没有顶点||不存在顶点m
		return;
	for(i=m; i<G->n-1; i++)//顶点m后面的顶点前移
		G->vexlist[i]=G->vexlist[i+1];

	//删除与第m个顶点相连的边
	//删掉边数
	for(i=0; i<G->n; i++)
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
    //减掉顶点数
	G->n--;
}
//判断v1和v2之间有没有边
bool IsEdge(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]!=0)
			return true;
		else
			return false;
	return false;
}
//在顶点v1和v2之间建立一条边
void SetSucc(MTGraph *G, int v1, int v2, EdgeData w)
{	
	if(!IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=w;	
		G->edge[v2][v1]=w;
		G->e++;
	}	
}

//删除v1和v2之间的边
void DelSucc(MTGraph *G, int v1, int v2)
{
	if(IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=0;
		G->edge[v2][v1]=0;
		G->e--;
	}	
}

//创建无向图
void CreateMGraph (MTGraph *G) 	
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
		cout<<"输入一条边的两个顶点和边的权值: ";
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
//显示无向图
void PrintMT(MTGraph *G)
{
	cout<<'\t';
	//输出顶点
	for(int i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';
	}
	cout<<endl;
	//输出每个顶点的连接关系
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