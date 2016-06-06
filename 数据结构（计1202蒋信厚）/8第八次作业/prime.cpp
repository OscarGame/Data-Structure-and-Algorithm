//Prime算法-图的邻接矩阵表示
#include<iostream.h>

#define NumEdges 50 			//边数
#define NumVertices 6 			//顶点个数
#define MAX_TREE_ARRAY 20
#define INT_MAX 1000
typedef char elementtype_tree_array;
typedef char VertexData; 		//顶点数据类型
typedef int EdgeData;			//边上权值类型

typedef struct{
    VertexData vexlist[NumVertices]; 	//顶点表
    EdgeData edge[NumVertices][NumVertices];
            		//邻接矩阵—边表, 可视为边之间的关系
    int n;			//图中当前的顶点个数
	int e; 			//图中当前的边数
} MTGraph;

void IniMGraph(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;
	G->n=0;
	G->e=0;
}

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

struct nodeTR
{
	int parent;
	elementtype_tree_array data;
};

typedef nodeTR TREE_ARRAY[MAX_TREE_ARRAY];
// 返回树T中第n个元素的右兄弟的下标，如果不存在，则返回0
int RightSibling(TREE_ARRAY T, int n)
{
	int i;
	for(i=n+1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].parent==T[n].parent)
			return i;
	}
	return 0;
}
// 返回树T中第n个元素的最左孩子的下标，如果不存在，则返回0
int LeftMostChild(TREE_ARRAY T, int n)
{
	int i;
	for(i=n+1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].parent==n)
			return i;
	}
	return 0;
}
//从第n个元素开始先根遍历树n，
void PreOrder(TREE_ARRAY T, int n)
{
	int c;
	cout<<T[n].data<<'\t';
	c=LeftMostChild(T, n);
	while(c!=0)
	{
		PreOrder(T, c);
		c=RightSibling(T, c);
	}
}
int Root(TREE_ARRAY T)
{
	int t;
	for(int i=1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].data!=' ')
		{
			t=i;
			while(1)
			{
				if(T[t].parent==0)
					return t;
				t=T[t].parent;

			}
		}

	}
}
//Prim算法
void Prim(MTGraph G, TREE_ARRAY T)
{   
	int i, j, k; 
	EdgeData min;//存储最小边长
	EdgeData LOWCOST[NumVertices];    // 如果第i个顶点未加入U，则LOWCOST[i]表示第i个顶点与U中距离最近的顶点之间的距离
	int CLOSSET[NumVertices];  //  如果第i个顶点未加入U，则LOWCOST[i]表示第i个顶点与U中距离最近的顶点
    //初始化
	int n=G.n;
	for( i=1; i<n; i++ )
	{ 
		LOWCOST[i] = G.edge[0][i];  //其他顶点与顶点i之间的距离
		CLOSSET[i] = 0; 
		T[i+1].data=G.vexlist[i];
		T[i+1].parent=0;
	}
	T[1].data=G.vexlist[0];//单独初始化第一个顶点
	T[1].parent=0;
	//找出最近的点
	for( i = 1; i < n; i++ )
	{   
		min = LOWCOST[i];    
		k = i;
		for( j = 1; j < n; j++ )
			if ( LOWCOST[j] < min )
			{   
				min = LOWCOST[j] ;
				k=j; 
			}

		cout << "第"<<i<<"个顶点的父亲："<< G.vexlist[CLOSSET[k]] <<'\t'<< "最近的顶点："<<G.vexlist[k] <<"最近距离为："<<G.edge[CLOSSET[k]][k]<< endl;  

		T[k].parent=CLOSSET[k];   //构建树：新加入结点为已有结点的孩子结点
		
		LOWCOST[k] = INT_MAX ;   // 标识第k个顶点已放入U中

		for ( j = 1; j < n; j++ )
			if ( G.edge[k][j] < LOWCOST[j] && LOWCOST[j]!=INT_MAX)
			{   
				LOWCOST[j]=G.edge[k][j]; 
				CLOSSET[j]=k; 
			}
	}
}
//======================================================================================
struct node_tmp{
	int i; 
	int j; 
	EdgeData v;
};

int Find(TREE_ARRAY T, int n)
{
	if(T[n].parent==n)
		return n;
	else
		Find(T, T[n].parent);
}

//将结点n的父节点设置为m
void Union(TREE_ARRAY T, int m, int n)
{
	if(Find(T, m)!=Find(T, n))
		T[n].parent=m;
}

void Kruskal(MTGraph G, TREE_ARRAY T)
{	
	int i, j, k;
	// 对树进行初始化，每一个结点构成一棵树，其父节点为它本身
	for(i=0; i<G.n; i++)
	{
		T[i+1].data=G.vexlist[i];
		T[i+1].parent=i+1;
	}

	node_tmp tmp[NumVertices*NumVertices], t1;
	k=0;
	for(i=0; i<G.n; i++)
		for(j=i+1; j<G.n; j++)
		{
			if(G.edge[i][j]!=INT_MAX-1)
			{
				tmp[k].i=i;
				tmp[k].j=j;
				tmp[k].v=G.edge[i][j];
				k++;
			}
		}
	
	// 按权值进行排序
	for(i=0; i<k-1; i++)
		for(j=i+1; j<k; j++)
		{
			if(tmp[i].v>tmp[j].v)
				t1=tmp[i], tmp[i]=tmp[j], tmp[j]=t1;
		}

	for(i=0; i<k; i++)
	{
		Union(T, tmp[i].i+1, tmp[i].j+1);
	}
	
	j=Find(T, 1);
	T[j].parent=0;
}
/*
void main()
{
	MTGraph G;
	IniMGraph(&G);

	VertexData v[6]={ 'a', 'b', 'c', 'd', 'e', 'f'};
	EdgeData e[6][NumVertices]={
								{INT_MAX-1,	1,			6,			INT_MAX-1,	INT_MAX-1,	5},
								{1,			INT_MAX-1,	5,			6,			4,			5},
								{6,			5,			INT_MAX-1,	3,			INT_MAX-1,	INT_MAX-1},
								{INT_MAX-1,	6,			3,			INT_MAX-1,	6,			INT_MAX-1},
								{INT_MAX-1,	4,			INT_MAX-1,	6,			INT_MAX-1,	2},
								{5,			5,			INT_MAX-1,	INT_MAX-1,	2,			INT_MAX-1}
								};
	CreateMGraph(&G, v, e, 6);

	int CLOSSET[NumVertices];
	TREE_ARRAY T;
	Kruskal(G, T);
    PreOrder(T, Root(T));
	cout<<endl;
}
*/
void main()
{
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={ 'a', 'b', 'c', 'd', 'e', 'f'};
	EdgeData e[6][6] = {
		{0,6,3,0,0,0},
		{6,0,0,1,0,5},
		{3,0,0,6,6,0},
		{0,1,6,0,0,5},
		{0,0,6,0,0,2},
		{0,5,0,5,2,0}
	};/*
	CreateMGraph(&G, v, e, 6);
	TREE_ARRAY T;
	Prim(G, T);
	PreOrder(T, 1);
	cout<<endl;
*/
	int CLOSSET[NumVertices];
	TREE_ARRAY T;
	Kruskal(G, T);
    PreOrder(T, Root(T));
	cout<<endl;
}
