#include "mtgraph.h"//邻接矩阵表示的图
#include "tree_array.h"//数组树

#ifdef _PRIME_
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

void main()
{
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={ 'a', 'b', 'c', 'd', 'e', 'f'};
	EdgeData e[6][6] = {{0,6,3,0,0,0},{6,0,0,1,0,5},{3,0,0,6,6,0},{0,1,6,0,0,5},{0,0,6,0,0,2},{0,5,0,5,2,0}};
	CreateMGraph(&G, v, e, 6);
	TREE_ARRAY T;
	Prim(G, T);
	PreOrder(T, 1);
	cout<<endl;
}

#endif