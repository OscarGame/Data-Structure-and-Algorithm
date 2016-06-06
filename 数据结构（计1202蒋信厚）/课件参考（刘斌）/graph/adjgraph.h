#ifndef _ADJGRAPH_H_
#define _ADJGRAPH_H_

#include "index.h"

#ifdef _ADJGRAPH_

#define NumVertices 10 			//顶点个数
typedef char VertexData; 		//顶点数据类型
typedef int EdgeData; 			//边上权值类型

typedef struct node { 			//边表结点
    int adjvex; 				//邻接点域(下标)
    EdgeData cost; 				//边上的权值
    struct node *next; 			//下一边链接指针
} EdgeNode;

typedef struct { 				//顶点表结点
    VertexData vertex; 			//顶点数据域
    EdgeNode * firstedge; 		//边链表头指针
} VertexNode;

typedef struct { 				//图的邻接表
    VertexNode vexlist[NumVertices+1];
    int n, e; 				//图中当前的顶点个数与边数
} AdjGraph;

// 以下函数适用于无向图
void CreateADJGraph(AdjGraph *G); 				//创建图
void CreateADJGraph(AdjGraph *G, VertexData [], EdgeData [][NumVertices], int n); //从给定的图的矩阵表示创建图，n为顶点的个数
void DelNode(AdjGraph *, int m);				//删除第m个顶点
BOOLEAN SetSucc(AdjGraph *G, int v1, int v2, EdgeData w);   // 建立v1和v2之间的一条边,权重为w
void DelSucc(AdjGraph *G, int v1, int v2);		// 删除v1和v2之间的一条边
BOOLEAN IsEdge(AdjGraph *G, int v1, int v2);	// 判断v1与v2之间是否有边相连

// 以下函数适用于有向图
void CreateADJGraph_directed(AdjGraph *G); 				//创建图
void CreateADJGraph_directed(AdjGraph *G, VertexData [], EdgeData [][NumVertices], int n); //从给定的图的矩阵表示创建图，n为顶点的个数
void DelNode_directed(AdjGraph *, int m);				//删除第m个顶点
BOOLEAN SetSucc_directed(AdjGraph *G, int v1, int v2, EdgeData w);   // 建立v1到v2的一条边,权重为w
void DelSucc_directed(AdjGraph *G, int v1, int v2);		// 删除v1到v2的一条边
BOOLEAN IsEdge_directed(AdjGraph *G, int v1, int v2);	// 判断v1到v2是否有边相连

//以下函数适用于有向图和无向图
void IniADJGraph(AdjGraph *);						// 初始化图
BOOLEAN NewNode(AdjGraph *, VertexData);			// 增加一个顶点
void PrintADJ(AdjGraph *G);

#endif

#endif