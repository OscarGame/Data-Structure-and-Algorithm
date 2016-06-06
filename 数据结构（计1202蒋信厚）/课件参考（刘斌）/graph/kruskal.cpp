#include "mtgraph.h"
#include "tree_array.h"


#ifdef _KRUSKAL_

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



#endif