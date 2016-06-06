#include<iostream.h>
#define NumVertices 6
#define NumEdges  8
typedef char VertexData;//顶点类型
typedef int EdgeData;//边权值类型

typedef struct{
    VertexData vexlist[NumVertices];//顶点集
    EdgeData edge[NumVertices][NumVertices];
    int n;
	int e;
} MTGraph;

bool visited[NumVertices];
int dfn[NumVertices];//深度优先编号

//深度优先搜索连通分量
void DFS2(MTGraph *G, int i)//从第i个顶点开始搜索
{
	int count = 0;//编号值
    cout << G->vexlist[i];//起点
    visited[i]=true;
    dfn[i]=count;//编号
    count++;
    for( int j=0; j<G->n; j++)
        if((G->edge[i][j]) && !visited[j] )//有边且未访问
            DFS2( G, j );//递归
}
void DFSTraverse(MTGraph G)//深度优先遍历
{   
    for ( int i = 0; i < G.n; i++ ) 
		visited [i] = false;//初始化顶点访问状态
    int count = 0;
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] ){
             count++;
             cout << count << ":";
             DFS2( &G, i );
        }
}

//后台默认直接创建
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

void main()
{
	//定义图
	MTGraph G;
    //定义边权值矩阵
    EdgeData e[NumEdges][NumVertices];
    //输入顶点个数
	cout<<"请输入顶点个数："<<endl;
	int n;
    cin >> n;
	//输入权值
	cout<<"请按行输入各边权值："<<endl;
    for (int i = 0; i < n; i++ )
        for ( int j = 0; j < n; j++ )
            cin >> e[i][j];	
    //顶点集
    VertexData v[NumEdges];
    for ( i = 0; i < n; i++ )
        v[i] = 'a' + i;	
	CreateMGraph(&G, v, e, n);
	DFSTraverse(G);
	cout<<endl;	
}