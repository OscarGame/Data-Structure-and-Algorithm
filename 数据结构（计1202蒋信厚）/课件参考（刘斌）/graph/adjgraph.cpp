#include "adjgraph.h"

#ifdef _ADJGRAPH_

VertexData freever='#';

void IniADJGraph(AdjGraph *G)						// 初始化图
{
	G->e=0;
	G->n=0;
	for(int i=1; i<NumVertices; i++)
	{
		G->vexlist[i].vertex=freever;
		G->vexlist[i].firstedge=NULL;		
	}
}

BOOLEAN NewNode(AdjGraph *G, VertexData v)		// 增加一个顶点，成功，返回TRUE，否则返回FALSE
{
	if(G->n<NumVertices-1)
	{
		for(int i=1; i<NumVertices; i++)
		{
			if(G->vexlist[i].vertex==freever)
			{
				G->vexlist[i].vertex=v;
				G->vexlist[i].firstedge=NULL;
				G->n++;
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

void DelNode(AdjGraph *G, int m)				//删除第m个顶点
{

	if(G->vexlist[m].vertex!=freever)			//如果第m个顶点存在
	{
		G->vexlist[m].vertex=freever;
		EdgeNode *p=G->vexlist[m].firstedge;
		while(p!=NULL)      // 删除与第m个顶点相连的边
		{
			DelSucc(G, m, p->adjvex);
			p=G->vexlist[m].firstedge;
		}
		G->vexlist[m].firstedge=NULL;

	}
}

BOOLEAN SetSucc(AdjGraph *G, int v1, int v2, EdgeData w)   // 建立v1和v2之间的一条边,权重为w
{
	if(G->vexlist[v1].vertex!=freever && G->vexlist[v2].vertex!=freever )   // v1和v2都为顶点
	{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(IsEdge(G, v1, v2))    //判断v1与v2之间是否存在边，若存在，则删除该边
			DelSucc(G, v1, v2);

		//为顶点v1增加边
		p = new EdgeNode; 		
        p->adjvex = v2;				
		p->cost = w; 	
        p->next = G->vexlist[v1].firstedge;
        G->vexlist[v1].firstedge = p;

		//为顶点v2增加边
		p = new EdgeNode; 		
        p->adjvex = v1;				
		p->cost = w; 	
        p->next = G->vexlist[v2].firstedge;
        G->vexlist[v2].firstedge = p;
		
		G->e++;    // 边数加1
		return TRUE;
	}
	return FALSE;
}

void DelSucc(AdjGraph *G, int v1, int v2)		// 删除v1和v2之间的一条边
{
	if(IsEdge(G, v1, v2))   // v1和v2都为顶点，且之间存在边
	{
		EdgeNode *p=G->vexlist[v1].firstedge, *p1;
		if(p->adjvex==v2)
		{
			p1=p;
			G->vexlist[v1].firstedge=p->next;
			G->e--;
			delete p1;
		}
		else
		{
			do
			{
				p1=p->next;
				if(p1==NULL)
					break;

				if(p1->adjvex==v2)
				{
					p->next=p1->next;
					delete p1;
					G->e--;
				}
				p=p->next;
			}while(p!=NULL);
		}

		p=G->vexlist[v2].firstedge;
		if(p->adjvex==v1)
		{
			p1=p;
			G->vexlist[v2].firstedge=p->next;
			delete p1;
		}
		else
		{
			do
			{
				p1=p->next;
				if(p1==NULL)
					break;

				if(p1->adjvex==v1)
				{
					p->next=p1->next;
					delete p1;				
				}
				p=p->next;
			}while(p!=NULL);
		}

	}
}

BOOLEAN IsEdge(AdjGraph *G, int v1, int v2)	// 判断v1与v2之间是否有边相连
{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(p==NULL)
			return FALSE;
		while(1)  
		{
			if(p->adjvex==v2)
			{
				return TRUE;
			}
			p=p->next;
			if(p==NULL)
				return FALSE;
		}
		return FALSE;
}

void CreateADJGraph (AdjGraph *G)
{   
	cout<<"输入顶点数和边数: ";
	cin >> G->n >> G->e; 					//1.输入顶点个数和边数
    for ( int i = 1; i <= G->n; i++)			//2.建立顶点表
	{ 		
		cout<<"输入第 "<<i<<" 个顶点信息: ";
        cin >> G->vexlist[i].vertex; 		//2.1输入顶点信息
        G->vexlist[i].firstedge = NULL;		//2.2边表置为空表
	}	
    for ( i = 1; i <= G->e; i++)				//3.逐条边输入,建立边表
	{ 		
		int tail, head;
		EdgeData weight;

		cout<<"输入第 "<<i<<" 条边的起始点、终止点以及权重: ";
        cin >> tail >> head >> weight; 		//3.1输入
        
		EdgeNode * p = new EdgeNode; 		//3.2建立边结点
        p->adjvex = head;					//3.3设置边结点
		p->cost = weight; 	
        p->next = G->vexlist[tail].firstedge; 	//3.4链入第tail 号链表的前端
        G->vexlist[tail].firstedge = p;
        
		p = new EdgeNode;
        p->adjvex = tail; 
		p->cost = weight;
        p->next = G->vexlist[head].firstedge; 	//链入第head 号链表的前端
        G->vexlist[head].firstedge = p; 
	}
}		 //时间复杂度：O(2e+n)

void CreateADJGraph(AdjGraph *G, VertexData V[], EdgeData E[][NumVertices], int n) //从给定的图的矩阵表示创建图，n为顶点的个数
{
	G->n=n;
	for ( int i = 1; i <= n; i++)			//2.建立顶点表
	{ 		
		G->vexlist[i].vertex=V[i-1]; 		//2.1输入顶点信息
        G->vexlist[i].firstedge = NULL;		//2.2边表置为空表
	}	
    for ( i = 1; i <=n; i++)				//3.逐条边输入,建立边表，由于对称性，只考虑上半角三角形
		for(int j=i+1; j<=n; j++)
		{ 		
		    if(E[i-1][j-1]!=0)
			{
				EdgeNode * p = new EdgeNode; 		//3.2建立边结点
				p->adjvex = j;					//3.3设置边结点
				p->cost = E[i-1][j-1]; 	
				p->next = G->vexlist[i].firstedge; 	//3.4链入第tail 号链表的前端
				G->vexlist[i].firstedge = p;
        
				p = new EdgeNode;
				p->adjvex = i; 
				p->cost = E[i-1][j-1];
				p->next = G->vexlist[j].firstedge; 	//链入第head 号链表的前端
				G->vexlist[j].firstedge = p; 
				G->e++;
			}
		}
}

void DelNode_directed(AdjGraph *G, int m)				//删除第m个顶点
{
	if(G->vexlist[m].vertex!=freever)			//如果第m个顶点存在
	{
		G->vexlist[m].vertex=freever;
		EdgeNode *p=G->vexlist[m].firstedge;
		while(p!=NULL)      // 删除与第m个顶点相连的边
		{
			DelSucc_directed(G, m, p->adjvex);
			p=G->vexlist[m].firstedge;
		}
		G->vexlist[m].firstedge=NULL;

		// 删除其他顶点指向第m个顶点的边
		for(int i=1; i<NumVertices; i++)
		{
			if(G->vexlist[i].vertex!=freever)
			{
				p=G->vexlist[i].firstedge;
				while(p!=NULL)
				{
					if(p->adjvex==m)
					{
						DelSucc_directed(G, i, m);
						break;
					}
					p=p->next;
				}
			}
		}
	}
}

BOOLEAN SetSucc_directed(AdjGraph *G, int v1, int v2, EdgeData w)   // 建立v1和v2之间的一条边,权重为w
{
	if(G->vexlist[v1].vertex!=freever && G->vexlist[v2].vertex!=freever )   // v1和v2都为顶点
	{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(IsEdge(G, v1, v2))    //判断v1与v2之间是否存在边，若存在，则删除该边
			DelSucc(G, v1, v2);

		//为顶点v1到v2增加边
		p = new EdgeNode; 		
        p->adjvex = v2;				
		p->cost = w; 	
        p->next = G->vexlist[v1].firstedge;
        G->vexlist[v1].firstedge = p;		
		
		G->e++;    // 边数加1
		return TRUE;
	}
	return FALSE;
}

void DelSucc_directed(AdjGraph *G, int v1, int v2)		// 删除v1和v2之间的一条边
{
	if(IsEdge(G, v1, v2))   // v1和v2都为顶点，且之间存在边
	{
		EdgeNode *p=G->vexlist[v1].firstedge, *p1;
		if(p->adjvex==v2)
		{
			p1=p;
			G->vexlist[v1].firstedge=p->next;
			G->e--;
			delete p1;
		}
		else
		{
			do
			{
				p1=p->next;
				if(p1==NULL)
					break;
				if(p1->adjvex==v2)
				{
					p->next=p1->next;
					delete p1;
					G->e--;
				}
				p=p->next;
			}while(p!=NULL);
		}
	}
}

BOOLEAN IsEdge_directed(AdjGraph *G, int v1, int v2)	// 判断v1与v2之间是否有边相连
{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(p==NULL)
			return FALSE;
		while(1)  
		{
			if(p->adjvex==v2)
			{
				return TRUE;
			}
			p=p->next;
			if(p==NULL)
				return FALSE;
		}
		return FALSE;
}

void CreateADJGraph_directed(AdjGraph *G)
{   
	cout<<"输入顶点数和边数: ";
	cin >> G->n >> G->e; 					//1.输入顶点个数和边数
    for ( int i = 1; i <= G->n; i++)			//2.建立顶点表
	{ 		
		cout<<"输入第 "<<i<<" 个顶点信息: ";
        cin >> G->vexlist[i].vertex; 		//2.1输入顶点信息
        G->vexlist[i].firstedge = NULL;		//2.2边表置为空表
	}	
    for ( i = 1; i <= G->e; i++)				//3.逐条边输入,建立边表
	{ 		
		int tail, head;
		EdgeData weight;

		cout<<"输入第 "<<i<<" 条边的起始点、终止点以及权重: ";
        cin >> tail >> head >> weight; 		//3.1输入
        
		EdgeNode * p = new EdgeNode; 		//3.2建立边结点
        p->adjvex = head;					//3.3设置边结点
		p->cost = weight; 	
        p->next = G->vexlist[tail].firstedge; 	//3.4链入第tail 号链表的前端
        G->vexlist[tail].firstedge = p;       
	}
}		 //时间复杂度：O(2e+n)

void CreateADJGraph_directed(AdjGraph *G, VertexData V[], EdgeData E[][NumVertices], int n) //从给定的图的矩阵表示创建图，n为顶点的个数
{
	G->n=n;
	for ( int i = 1; i <= n; i++)			//2.建立顶点表
	{ 		
		G->vexlist[i].vertex=V[i-1]; 		//2.1输入顶点信息
        G->vexlist[i].firstedge = NULL;		//2.2边表置为空表
	}	
    for ( i = 1; i <=n; i++)				//3.逐条边输入,建立边表，由于对称性，只考虑上半角三角形
		for(int j=1; j<=n; j++)
		{ 		
		    if(E[i-1][j-1]!=0)
			{
				EdgeNode * p = new EdgeNode; 		//3.2建立边结点
				p->adjvex = j;					//3.3设置边结点
				p->cost = E[i-1][j-1]; 	
				p->next = G->vexlist[i].firstedge; 	//3.4链入第tail 号链表的前端
				G->vexlist[i].firstedge = p;        
				G->e++;
			}
		}
}

void PrintADJ(AdjGraph *G)
{
	EdgeNode * p;
	int i, j;
	EdgeData result[NumVertices][NumVertices]={0};
	VertexData ver[NumVertices];

	cout<<'\t';
	for(i=1; i<NumVertices; i++)
	{
		cout<<G->vexlist[i].vertex<<'\t';
		ver[i]=G->vexlist[i].vertex;
	}
	cout<<endl;
	
	for(i=1; i<NumVertices; i++)
	{	
		p=G->vexlist[i].firstedge;
		while(p!=NULL)
		{
			result[i][p->adjvex]=p->cost;
			p=p->next;
		}
	}

	for(i=1; i<NumVertices; i++)
	{
		cout<<ver[i]<<'\t';
		for(j=1; j<NumVertices; j++)
		{
			cout<<result[i][j]<<'\t';
		}
		cout<<endl;
	}
	cout<<endl;
}


#ifndef _DFS_
#ifndef _BFS_
#ifndef _AOV_

void main()
{/*		
	cout<<"无向图:"<<endl;
	AdjGraph G;
	IniADJGraph(&G);
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={{0, 1, 0, 1, 0},
								{1, 0, 1, 1, 1},
								{0, 1, 0, 1, 0},
								{1, 1, 1, 0, 1},
								{0, 1, 0, 1, 0}};
	
		          
	CreateADJGraph(&G, v, e, 5);
	cout<<G.n<<' '<<G.e<<endl;

	//CreateADJGraph(&G);

	NewNode(&G, 'a');
	NewNode(&G, 'b');
	NewNode(&G, 'c');
	NewNode(&G, 'd');
	NewNode(&G, 'e');

	cout<<G.n<<' '<<G.e<<endl;

	SetSucc(&G, 1, 2, 1);
	SetSucc(&G, 1, 4, 1);
	SetSucc(&G, 1, 5, 1);
	SetSucc(&G, 2, 3, 1);
	SetSucc(&G, 2, 4, 1);
	SetSucc(&G, 3, 4, 1);
	SetSucc(&G, 3, 5, 1);
	SetSucc(&G, 4, 5, 1);
	SetSucc(&G, 2, 4, 3);
	cout<<G.n<<' '<<G.e<<endl;

	DelSucc(&G, 3, 4);
	cout<<G.n<<' '<<G.e<<endl;

	DelNode(&G, 2);
	cout<<G.n<<' '<<G.e<<endl;

	PrintADJ(&G);
*/
	

	cout<<"有向图:"<<endl;
	AdjGraph G1;
	IniADJGraph(&G1);

  	VertexData v1[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e1[5][NumVertices]={{0, 1, 0, 1, 0},
								{1, 0, 0, 1, 1},
								{0, 1, 0, 1, 0},
								{1, 0, 1, 0, 1},
								{0, 1, 0, 1, 0}};
	
		          
	CreateADJGraph_directed(&G1, v1, e1, 5);
	cout<<G1.n<<' '<<G1.e<<endl;
/*
	//CreateADJGraph_directed(&G1);
	
	NewNode(&G1, 'a');
	NewNode(&G1, 'b');
	NewNode(&G1, 'c');
	NewNode(&G1, 'd');
	NewNode(&G1, 'e');



	SetSucc_directed(&G1, 1, 2, 1);
	SetSucc_directed(&G1, 1, 4, 1);
	SetSucc_directed(&G1, 1, 5, 1);
	SetSucc_directed(&G1, 2, 3, 1);
	SetSucc_directed(&G1, 2, 4, 1);
	SetSucc_directed(&G1, 3, 4, 1);
	SetSucc_directed(&G1, 3, 5, 1);
	SetSucc_directed(&G1, 4, 5, 1);
	SetSucc_directed(&G1, 2, 4, 3);
	cout<<G1.n<<' '<<G1.e<<endl;

	DelSucc_directed(&G1, 3, 4);
	cout<<G1.n<<' '<<G1.e<<endl;

	DelNode_directed(&G1, 2);
	cout<<G1.n<<' '<<G1.e<<endl;
*/
	PrintADJ(&G1);

}

#endif
#endif
#endif
#endif