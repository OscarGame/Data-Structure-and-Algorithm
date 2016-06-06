#ifndef _INDEX_H_
#define _INDEX_H_


#include <iostream>
#include <string>
#include <stdio.h>
//#include <limits.h>

using namespace std;

enum BOOLEAN{FALSE, TRUE};
//#define MaxValue INT_MAX		//在<limits.h>中

// 队列
//#define _QUEUE_

// 用邻接矩阵表示的树
//#define _TREE_ARRAY_

//邻接矩阵表示的图
#define _MTGRAPH_

//邻接表表示的图
//#define _ADJGRAPH_

//深度优先遍历，需要上述两种表示方法中的一种方法
//#define _DFS_

//深度优先遍历，需要上述两种表示方法中的一种方法以及队列
//#define _BFS_

//最小生成树-prime算法，需要邻接矩阵表示的图和邻接矩阵表示的树
//#define _PRIME_

// 最小生成树-Kruskal算法，需要邻接矩阵表示的图和邻接矩阵表示的树
//#define _KRUSKAL_

//拓扑排序，AOV网，以教学计划为例，需要队列和邻接表表示的图
//#define _AOV_

//关键路径，AOE网，需要拓扑排序、队列和邻接表表示的图
//#define _AOE_

// 单源最短路径 Dijkstra，需要邻接矩阵表示的图
//#define _DIJKSTRA_

// Floyd算法、Warshall算法、求有向图的中心点，需要邻接矩阵表示的图
#define _FLOYD_

#endif



