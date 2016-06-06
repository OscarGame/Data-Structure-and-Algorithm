#include "aov.h"

#ifdef _AOE_

//AOE关于边的活动网，求关键路径（活动的最早发生时间，最迟发生时间）
void aoe(AdjGraph G, int start)// 参数start为起始点的下标
{
	int i, j;
	EdgeData E[NumVertices][NumVertices], VE[NumVertices], L[NumVertices][NumVertices], VL[NumVertices];
	int aov[NumVertices];
	EdgeNode *tmp;
	
	//对所有事件进行拓扑排序，排序结果放置在数组aov中
	Topologicalsort( G, aov);
	
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			E[i][j]=-1;
			L[i][j]=-1;
		}

	// 求VE[i]事件i的最早发生时间
	VE[aov[0]-1]=0;//起点
	for(i=1; i<G.n; i++)    // 对拓扑排序后的顶点aov[i]按序处理
	{	
		VE[aov[i]-1]=0;
		for(j=0; j<i; j++)  // 搜索顶点aov[i]的所有前驱顶点
		{
			tmp=G.vexlist[aov[j]].firstedge;  // 邻接表表示的图的顶点的下标是从1开始的
			while(1)
			{
				if(tmp==NULL)
					break;
				else if(tmp->adjvex==aov[i])
				{
					if(tmp->cost+VE[aov[j]-1]>VE[aov[i]-1])	// 根据搜索到的前驱顶点求当前顶点的VE
						VE[aov[i]-1]=tmp->cost+VE[aov[j]-1];					
				}
				tmp=tmp->next;
			}
		}
	}
	cout<<"v3的最早发生时间："<<VE[3]<<endl;
	// 求E[i][j]
	for(i=0; i<G.n; i++)
	{	
		tmp=G.vexlist[i+1].firstedge;   //搜索第i+1个顶点的出边
		while(1)
		{
			if(tmp==NULL)
				break;
			else
			{
				E[i][tmp->adjvex-1]=VE[aov[i]-1];
			}
			tmp=tmp->next;
		}
	}	

	//求VL[i]事件i的最迟发生时间，转化为求最早发生时间问题
	VL[aov[G.n-1]-1]=VE[aov[G.n-1]-1];
	for(i=G.n-2; i>=0; i--)       // 对拓扑排序后的顶点aov[i]按逆序处理
	{
		VL[aov[i]-1]=VE[aov[G.n-1]-1];
		tmp=G.vexlist[aov[i]].firstedge;  // 邻接表表示的图的顶点的下标是从1开始的
		while(1)   // 搜索顶点aov[i]的所有后继节点
		{
			if(tmp==NULL)
				break;
			else 
			{
				if(VL[aov[i]-1]>VL[tmp->adjvex -1]-tmp->cost)				
					VL[aov[i]-1]=VL[tmp->adjvex -1]-tmp->cost;					
			}
			tmp=tmp->next;
		}
		
	}

	// 求L[i][j]
	for(i=0; i<G.n; i++)
	{	
		tmp=G.vexlist[i+1].firstedge; // 搜索第i+1个顶点的出边
		while(1)
		{
			if(tmp==NULL)
				break;
			else
			{
				L[i][tmp->adjvex-1]=VL[aov[tmp->adjvex-1]-1]-tmp->cost;
			}
			tmp=tmp->next;
		}		
	}	

	//输出关键活动
	cout<<"关键活动为: "<<endl;
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			if(E[i][j]!=-1 && L[i][j]!=-1 && E[i][j]==L[i][j])
				cout<<i+1<<"->"<<j+1<<endl;
		}
}

void main()
{
	AdjGraph G1;
	IniADJGraph(&G1);
	// 创建一个有向图
  	VertexData v1[9]={'v1', 'v2', 'v3', 'v4', 'v5','v6'};
	EdgeData e1[9][NumVertices]={{0, 6, 0, 4, 0, 0},
								{0, 0, 7, 0, 0, 0},
								{0, 0, 0, 0, 9, 11},
								{0, 0, 8, 0, 0, 21},
								{0, 0, 0, 0, 0, 3},
								{0, 0, 0, 0, 0, 0}};
	CreateADJGraph_directed(&G1, v1, e1, 6);

	aoe(G1, 0);
}

#endif