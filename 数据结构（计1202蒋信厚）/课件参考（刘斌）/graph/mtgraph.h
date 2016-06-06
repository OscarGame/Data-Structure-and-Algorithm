#ifndef _MTGRAPH_H_
#define _MTGRAPH_H_

//#include "index.h"

#ifdef _MTGRAPH_	

#define NumEdges 50 			//边数
//#define NumVertices 10 			//顶点个数

typedef char VertexData; 		//顶点数据类型
typedef int EdgeData;			//边上权值类型

typedef struct{
    VertexData vexlist[NumVertices]; 	//顶点表
    EdgeData edge[NumVertices][NumVertices];
            		//邻接矩阵—边表, 可视为边之间的关系
    int n;			//图中当前的顶点个数
	int e; 			//图中当前的边数
} MTGraph;

// 以下函数适用于无向图
void CreateMGraph (MTGraph *G); 			//建立(无向)图的邻接矩阵
void CreateMGraph(MTGraph *G, VertexData [], EdgeData [][NumVertices], int n);   // 通过给定的数组构建无向图，n为顶点的个数
void IniMGraph(MTGraph *);					// 初始化图
void NewNode(MTGraph *, VertexData);  // 增加一个顶点,(无向)图
void DelNode(MTGraph *, int m);				//删除第m个顶点,(无向)图
void SetSucc(MTGraph *G, int v1, int v2, EdgeData w);   // 建立v1和v2之间的一条边,权重为w
void DelSucc(MTGraph *G, int v1, int v2);   // 删除v1和v2之间的一条边,权重为w
BOOLEAN IsEdge(MTGraph *G, int v1, int v2); // 判断v1与v2之间是否有边相连


// 以下函数适用于有向图

void CreateMGraph_directed (MTGraph *G); 			//建立图的邻接矩阵
void CreateMGraph_directed(MTGraph *G, VertexData [], EdgeData [][NumVertices], int n);   // 通过给定的数组构建有向图图，n为顶点的个数
void IniMGraph_directed(MTGraph *);					// 初始化图
void NewNode_directed(MTGraph *, VertexData);  // 增加一个顶点,有向图
void DelNode_directed(MTGraph *, int m);				//删除第m个顶点,有向图
void SetSucc_directed(MTGraph *G, int v1, int v2, EdgeData w);   // 建立v1和v2之间的一条边,权重为w
void DelSucc_directed(MTGraph *G, int v1, int v2);   // 删除v1和v2之间的一条边,权重为w
BOOLEAN IsEdge_directed(MTGraph *G, int v1, int v2); // 判断v1与v2之间是否有边相连


// 以下函数使用与无向图和有向图
void PrintMT(MTGraph *G);



#endif

#endif