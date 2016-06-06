#include<iostream.h>

#define MaxValue 1000
#define NumEdges 50 			//边数
#define NumVertices 6 			//顶点个数

typedef char VertexData; 		//顶点数据类型
typedef int EdgeData;			//边上权值类型

typedef struct{
    VertexData vexlist[NumVertices]; 	//顶点表
    EdgeData edge[NumVertices][NumVertices];
            		//邻接矩阵—边表, 可视为边之间的关系
    int n;			//图中当前的顶点个数
	int e; 			//图中当前的边数
} MTGraph;

// 有向图
void IniMGraph_directed(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=MaxValue;
	G->n=0;
	G->e=0;
}

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
//Floyd算法求每对顶点之间的最短路径
void Floyd(int A[NumVertices][NumVertices],MTGraph C,int P[NumVertices][NumVertices],int n)
{   
	int i, j, k;
	for ( i = 0; i < n; i++ )
        for ( j = 0; j<n; j++ )
		{
            A[i][j] = C.edge[i][j] ;       
			P[i][j] = -1; 
    } 

    for ( k = 0; k < n; k++ )
        for ( i = 0; i < n; i++ )
            for ( j = 0; j <n; j++ )
                  if ( A[i][k] + A[k][j] < A[i][j] )
				  {
                        A[i][j] = A[i][k] + A[k][j] ;   
						P[i][j] = k;
				  }
} /* 时间复杂性O(n3) */

void Path(int P[NumVertices][NumVertices], int i, int j)
{
	int k=P[i][j];
	if(k!=-1)
	{
		Path(P, i, k);
		cout<<k+1<<endl;
		Path(P, k, j);
	}
	
}

//Warllshall算法求邻接矩阵的传递闭包
void Warshall(int A[NumVertices][NumVertices],MTGraph C,int n)
{
	int i, j, k;
	for ( i = 0; i < n; i++ )
        for ( j = 0; j<n; j++ )
		{
            if(C.edge[i][j]!=MaxValue)			
				A[i][j] =1 ; 				
			else			
				A[i][j]=0;
		
			
    } 
    for ( k = 0; k < n; k++ )
        for ( i = 0; i < n; i++ )
            for ( j = 0; j <n; j++ )
                  if ( A[i][k] && A[k][j] )
				  {
                        A[i][j] =A[i][j] || ( A[i][k] && A[k][j]) ; 					
				  }
} /* 时间复杂性O(n3) */

//求中心点
void CenterPoint(EdgeData A[NumVertices][NumVertices], int n, int &cp)
{
	EdgeData E[NumVertices]={0};
	int min=MaxValue;
	for(int j=0; j<n; j++)
	{
		for(int i=0; i<n; i++)
			if(A[i][j]<MaxValue)
				E[j]+=A[i][j];
		if(E[j]==0)
			E[j]=MaxValue;
		if(E[j]<min)
		{
			min=E[j];
			cp=j;
		}
	}		
}

void main()
{
	int i, j, cp;
	MTGraph G;
	IniMGraph_directed(&G);
	VertexData v[]={'a', 'b', 'c', 'd', 'e','f'};//顶点集
	EdgeData e[NumVertices][NumVertices]={
		{0,3,MaxValue,4,MaxValue,5},
		{MaxValue,0,1, MaxValue, MaxValue,1},
		{MaxValue, MaxValue,0,2,MaxValue,MaxValue},
		{MaxValue,3,MaxValue,0,MaxValue,MaxValue},
		{MaxValue, MaxValue, MaxValue,3,0,2},
		{MaxValue,MaxValue,MaxValue,2,MaxValue,0}
	};//边集，邻接矩阵
	CreateMGraph_directed(&G, v, e, 6);

	EdgeData A[NumVertices][NumVertices]={0};
	int A1[NumVertices][NumVertices]={0};
	int P[NumVertices][NumVertices];
	
	Floyd(A, G, P, G.n);
	cout<<"每一对顶点之间的最短路径:"<<endl;
	for(i=0; i<G.n; i++)
	{
		for(int j=0; j<G.n; j++)
			cout<<A[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"相通节点之间的路径长以及中间节点: "<<endl;
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			if(A[i][j]<MaxValue)
			{
				cout<<G.vexlist[i]<<"->"<<G.vexlist[j]<<", 最短路径长度: "<<A[i][j]<<", 中间结点"<<':'<<endl;;		
				Path(P, i, j);
			}
		}
//求传递闭包
	Warshall(A1, G, G.n);
	cout<<"\n传递闭包为:"<<endl;
	for(i=0; i<G.n; i++)
	{
		for(int j=0; j<G.n; j++)
			cout<<A1[i][j]<<'\t';
		cout<<endl;
	}
//求中心节点
	CenterPoint(A, G.n, cp);
	cout<<"\n\n中心点为: "<<G.vexlist[cp+1]<<endl;

}
