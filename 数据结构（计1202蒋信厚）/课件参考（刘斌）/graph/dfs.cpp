#include "adjgraph.h"
#include "mtgraph.h"

#ifdef _DFS_

#ifdef _ADJGRAPH_
// 连接表表示
BOOLEAN visited[NumVertices]; 	//访问标记数组是全局变量
int dfn[NumVertices]; 			//顶点的先深编号

void DFS1 (AdjGraph* G, int i);

void DFSTraverse(AdjGraph G)
//先深搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =FALSE; 		//标志数组初始化
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS1( &G, i+1 ); //从顶点i 出发开始搜索search() DFSX(G, i )
}

void DFS1 (AdjGraph* G, int i)//以vi为出发点时对邻接表表示的图G进行先深搜索
{   
	static int count=0;
	EdgeNode *p;
    cout<<G->vexlist[i].vertex;		//访问顶点vi;
    visited[i]=TRUE;	 			//标记vi已访问
    dfn[i]=count++; 				//对vi进行编号
    p=G->vexlist[i].firstedge; 		//取vi边表的头指针
    while( 1 )						//依次搜索vi的邻接点vj, 这里j=p->adjvex
	{ 			
        if( !visited[p->adjvex] ) 	//若vj尚未访问
            DFS1(G, p->adjvex); 	//则以vj为出发点先深搜索
        p=p->next;
		if(p==NULL)
			break;
    }	
} //DFS1

void main()
{
	AdjGraph G;
	IniADJGraph(&G);
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={{0, 1, 0, 1, 0},
								{1, 0, 1, 1, 0},
								{0, 1, 0, 1, 0},
								{1, 1, 1, 0, 1},
								{0, 0, 0, 1, 0}};	
		          
	CreateADJGraph(&G, v, e, 5);
	DFSTraverse(G);
	cout<<endl;
}

#endif

//连接矩阵表示
#ifdef _MTGRAPH_

BOOLEAN visited[NumVertices]; 	//访问标记数组是全局变量
int dfn[NumVertices]; 			//顶点的先深编号

void DFS2(MTGraph *G, int i);

void DFSTraverse(MTGraph G)
//先深搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =FALSE; 		//标志数组初始化
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS2( &G, i ); //从顶点i 出发开始搜索search() DFSX(G, i )
}

void DFS2(MTGraph *G, int i)//以vi为出发点对邻接矩阵表示的图G进行深度优先搜索
{ 
    int j;
	static int count=0;
    cout<<G->vexlist[i]; 	//访问定点vi
    visited[i]=TRUE; 	//标记vi已访问
    dfn[i]=count; 		//对vi进行编号
    count ++; 		//下一个顶点的编号
    for( j=0; j<G->n; j++) 	//依次搜索vi的邻接点
        if((G->edge[i][j] == 1) && !visited[j] ) 	//若vj尚未访问
            DFS2( G, j );
}//DFS2

void main()
{
	MTGraph G;
	IniMGraph(&G);

	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={
								{0, 1, 0, 1, 1},
								{1, 0, 1, 0, 0},
								{0, 1, 0, 0, 1},
								{1, 0, 0, 0, 1},
								{1, 0, 1, 1, 0}};
	CreateMGraph(&G, v, e, 5);
	PrintMT(&G);

	DFSTraverse(G);
	cout<<endl;

}


#endif
#endif