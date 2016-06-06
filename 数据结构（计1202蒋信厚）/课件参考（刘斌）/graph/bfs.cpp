
#include "index.h"
#include "adjgraph.h"
#include "mtgraph.h"
#include "queue.h"

#ifdef _BFS_

#ifdef _ADJGRAPH_
//广度优先搜索-链表表示
BOOLEAN visited[NumVertices]; 	//访问标记数组是全局变量
int bfn[NumVertices]; 			//顶点的先深编号

void BFS1 (AdjGraph *G, int k)   //这里没有进行广度优先编号
{   
	int i; 
	EdgeNode *p; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ] .vertex;   
	visited[ k ] = TRUE;
    ENQUEUE (k, Q); 			//进队列
    while ( !EMPTY (Q) ) 		//队空搜索结束
	{ 	
        i=FRONT(Q)->element;
		DEQUEUE(Q); 			//vi出队
        p =G->vexlist[ i ].firstedge; 	//取vi的边表头指针
        while ( p ) 			//若vi的邻接点vj (j= p->adjvex)存在,依次搜索
		{ 
			if (!visited[p->adjvex ])  	//若vj未访问过
			{
				cout << G->vexlist[ p->adjvex ].vertex;	//访问vj
				visited[ p->adjvex ]=TRUE; 		//给vj作访问过标记
				ENQUEUE ( p->adjvex , Q ); 		//访问过的vj入队
        	}
            p = p->next; 	//找vi的下一个邻接点
        } 	//重复检测vi的所有邻接顶点
    } 		//外层循环，判队列空否
}			//以vk为出发点时对用邻接表表示的图G进行先广搜索

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

	BFS1(&G, 1);
	cout<<endl;
}

#endif

#ifdef _MTGRAPH_

BOOLEAN visited[NumVertices]; 	//访问标记数组是全局变量
int bfn[NumVertices]; 			//顶点的先深编号

void BFS2 (MTGraph *G, int k)	//这里没有进行先广编号
{   
	int i , j; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ]; 		//访问vk
    visited[ k ] = TRUE; 			//给vk作访问过标记
    ENQUEUE (k, Q); 				// vk进队列
    while ( ! EMPTY (Q) )			//队空时搜索结束
	{ 		
        i=FRONT(Q)->element;
		DEQUEUE(Q); 				//vi出队
        for(j=0; j<G->n; j++) { 	//依次搜索vi的邻接点vj
            if ( G->edge[ i ][ j ] ==1 && !visited[ j ]) //若vj未访问过
			{ 	
                cout << G->vexlist[ j ];		//访问vj
				visited[j]=TRUE; 				//给vj作访问过标记
				ENQUEUE( j , Q ); 				//访问过的vj入队
            }
        } 		//重复检测vi的所有邻接顶点
    } 			//外层循环，判队列空否
} 				//以vk为出发点时对用邻接矩阵表示的图G进行先广搜索

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

	BFS2(&G, 0);
	cout<<endl;
}

#endif
#endif