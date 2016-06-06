#include "aov.h"

#ifdef _AOV_

// 判断从顶点v1到顶点v2是否存在边
BOOLEAN connect(AdjGraph G, int v1, int v2)
{
	EdgeNode *tmp;
	tmp=G.vexlist[v1].firstedge;
	if(tmp==NULL)
		return FALSE;
	while(1)
	{
		if(tmp->adjvex==v2)
			return TRUE;
		tmp=tmp->next;
		if(tmp==NULL)
			break;
	}

	return FALSE;
}

void Topologicalsort( AdjGraph G, int aov[NumVertices] )
{  
	int v, w, nodes;
	EdgeNode *tmp;
	EdgeData indegree[NumVertices+1]={0};

	QUEUE Q ;
	MAKENULL( Q ) ;

	// 计算每个顶点的入度
	for( v=1; v<=G.n ; ++v )
	{
		tmp=G.vexlist[v].firstedge;
		while(tmp)
		{
			indegree[tmp->adjvex]++;
			tmp=tmp->next;
		}	
	}
	// 将入度为0的顶点加入队列
	for(v=1; v<=G.n; ++v)
		if ( indegree[v] ==0 ) 
			ENQUEUE( v, Q ) ;
	
	nodes = 0 ;
	while ( !EMPTY( Q ) )
	{  
		v = FRONT(Q)->element ;
		DEQUEUE( Q ) ;
		//cout << v <<' '; 
		aov[nodes]=v;
		nodes ++ ;		// 已考虑的节点个数加1
		// 如果(v, w)是一条边，将w的入度减1，如果w的入度为0，则将w入队
		for( w=1; w<=G.n; w++) 
		{
			if(connect(G, v, w))
			{
				--indegree[w];
				if( !(indegree[w])) 
					ENQUEUE(w,Q) ;
			}
		}
	}
	cout<<endl;
	if ( nodes < G.n ) 
		cout<<"图中有环路"<<endl;
	
}

#ifndef _AOE_

void main()
{

	AdjGraph G1;
	IniADJGraph(&G1);
	// 以课程为例，创建一个有向图
  	VertexData v1[10]={'a', 'b', 'c', 'd', 'e','f', 'g', 'h', 'i', 'j'};
	EdgeData e1[10][NumVertices]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
								{0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	
		          
	CreateADJGraph_directed(&G1, v1, e1, 10);
	int aov[NumVertices];
	Topologicalsort( G1, aov);
	for(int i=0; i<10; i++)
		cout<<aov[i]<<' ';
	cout<<endl;
}

#endif
#endif