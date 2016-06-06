//Dijikstra算法用于求图的单源最短路径以及每一对顶点之间的最短路径
#include<iostream>
#include<string>
using namespace std;
#define MaxValue 1000//此处用1000表示无穷大
enum BOOLEAN{FALSE, TRUE};
//此程序中的图采用邻接矩阵表示
#define NumEdges 50 			//边数
#define NumVertices 6			//顶点个数

typedef string VertexData; 		//顶点数据类型
typedef int EdgeData;			//边上权值类型

typedef struct{
    VertexData vexlist[NumVertices]; 	//顶点表
    EdgeData edge[NumVertices][NumVertices];
            		//邻接矩阵—边表, 可视为边之间的关系
    int n;			//图中当前的顶点个数
	int e; 			//图中当前的边数
} MTGraph;

void IniMGraph_directed(MTGraph *G)//初始化有向图
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=MaxValue;
	G->n=0;
	G->e=0;
}
//创建有向图
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
//输出有向图的邻接矩阵
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
//求V-S中使D[w]最小的w值
int mincost(EdgeData D[NumVertices], BOOLEAN S[NumVertices], int n)
{   
	int w;
	EdgeData temp =MaxValue ;  //用MaxValue表示无穷大
	w=0;
    for (int i=1 ; i<n ; i++ )
		if (!S[i] && D[i]<temp)//搜索D[]中最小且未放入S中的顶点的权
		{   
			temp = D[i] ;
            w = i ;
        }
    return w ;
}

// 单源最短路径-Dijkstra算法
void Dijkstra(MTGraph G, EdgeData D[NumVertices], int P[NumVertices])
//D[]记录源点到其余各顶点当前的最短路径长度
{
	BOOLEAN S[NumVertices]={FALSE};//标记顶点是否已经确定最短路径，确定的标记为TRUE
	int i, v, w;
	EdgeData sum;

    D[0]=MaxValue;//数组第一个位置表示源点到自身的距离，初始化为无穷
//初始化为初态，此算法规定第一个顶点为源点
	for ( i=1 ; i<G.n; i++ )
    { 
		D[i]=G.edge[0][i] ; 
		S[i]=FALSE ; 
	}
    S[0]= TRUE;//初态将源点放入S中
    for(i=1; i<G.n; i++)
    {   
		w=mincost ( D, S, G.n );
        S[w]=TRUE ;//将w放入S中
        for ( v=1 ; v<G.n ; v++ )
            if ( S[v]!=TRUE && G.edge[w][v]!=MaxValue)//顶点v未访问过并且顶点v-w之间有边
            { 
				sum=D[w] + G.edge[w][v] ;
                if (sum < D[v] ) 
					D[v] = sum ; 
				P[v]=w; //保留最短路径上v的直接前导结点
			}
   } 
}
/*
void Path(int P[],VertexData v[],int input)//输出源点到顶点input的最短路径
{
	cout<<"源点到顶点<<v[input]<<的最短路径为："<<endl;
	for(int i=0;P[i]!=input;i++)
	{
		cout<<v[P[i]]<<"-->";
	}
	cout<<v[v]<<endl;
}
*/
void main()
{
	MTGraph G;
	IniMGraph_directed(&G);
	VertexData v[6]={"v1", "v2", "v3", "v4", "v5" , "v6"};//顶点数组
	EdgeData e[6][NumVertices]={
		{0,45,15,MaxValue,15,MaxValue},
		{MaxValue,0,MaxValue,20,15,15},
		{10,10,0,60,MaxValue,MaxValue},
		{MaxValue,30,MaxValue,0,MaxValue,20},
		{MaxValue,MaxValue,MaxValue,MaxValue,0,MaxValue},
		{MaxValue,MaxValue,MaxValue,MaxValue,MaxValue,0}
	};//邻接矩阵
	CreateMGraph_directed(&G, v, e, 6);//创建
	cout<<"有向图的邻接矩阵："<<endl;
	PrintMT(&G);
	cout<<endl;
	EdgeData D[6]; //记录源点到其余各顶点当前的最短路径长度
	int P[6]={0};//P[v]是记录最短路径上的顶点v之前的顶点
	Dijkstra(G, D, P);
	cout<<"单源最短路径长度：";
	for(int i=1; i<6; i++)
		cout<<D[i]<<'\t';
	cout<<endl;
	cout<<"随着算法的进行D[w]变动时所得D[w]的路线变动情况："<<endl;
	for(i=1; i<6; i++)
		cout<<G.vexlist[P[i]]<<"->"<<G.vexlist[i]<<endl;
	cout<<endl;
}
