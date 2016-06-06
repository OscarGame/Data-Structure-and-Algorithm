//邻接表表示：
#include<iostream>
using namespace std;

#define freever '#'
#define NumVertices 6 			//顶点个数
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

void IniADJGraph(AdjGraph *G)						
{
	G->e=0;
	G->n=0;
	for(int i=1; i<NumVertices; i++)
	{
		G->vexlist[i].vertex=freever;
		G->vexlist[i].firstedge=NULL;		
	}
}
bool NewNode(AdjGraph *G, VertexData v)// 增加一个顶点，成功，返回true，否则返回false	
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
				return true;
			}
		}
	}	
	return false;
}

bool IsEdge(AdjGraph *G, int v1, int v2)	// 判断v1与v2之间是否有边相连
{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(p==NULL)
			return false;
		while(1)  
		{
			if(p->adjvex==v2)
			{
				return true;
			}
			p=p->next;
			if(p==NULL)
				return false;
		}
		return false;
}

void DelSucc(AdjGraph *G, int v1, int v2)	// 删除v1和v2之间的一条边
{
	if(IsEdge(G, v1, v2)) 
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

bool SetSucc(AdjGraph *G, int v1, int v2, EdgeData w)   // 建立v1和v2之间的一条边,权重为w
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
		return true;
	}
	return false;
}

void CreateADJGraph(AdjGraph *G)
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
        p->next = G->vexlist[head].firstedge; 	
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
		for(int j=1; j<=n; j++)
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
				p->next = G->vexlist[j].firstedge; 	
				G->vexlist[j].firstedge = p; 
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
void main()
{
	/*
     cout<<"无向图:"<<endl;
	AdjGraph G;
	IniADJGraph(&G);
	VertexData v[6]={'v1', 'v2', 'v3', 'v4', 'v5','v6'};
	EdgeData e[6][NumVertices]={{0, 1, 0, 1, 0, 1},
								{1, 0, 1, 1, 1, 0},
								{0, 1, 0, 0, 1, 0},
								{1, 1, 0, 0, 1, 1},
								{0, 1, 1, 1, 0, 0},
                                                                                                                               {1, 0, 0, 1, 0, 0}};
	
		          
	CreateADJGraph(&G, v, e, 6);
	cout<<G.n<<' '<<G.e<<endl;
	NewNode(&G, 'v1');
	NewNode(&G, 'v2');
	NewNode(&G, 'v3');
	NewNode(&G, 'v4);
	NewNode(&G, 'v5');
	NewNode(&G, 'v6');

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
}