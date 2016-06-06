//邻接表表示：
#include<iostream>
using namespace std;

#define freever '#'
#define NumVertices 4 			//顶点个数
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

bool IsEdge_directed(AdjGraph *G, int v1, int v2)// 判断v1与v2之间是否有边相连	
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

void DelSucc_directed(AdjGraph *G, int v1, int v2)		// 删除v1和v2之间的一条边
{
	if(IsEdge_directed(G, v1, v2))   // v1和v2都为顶点，且之间存在边
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

bool SetSucc_directed(AdjGraph *G, int v1, int v2, EdgeData w)   // 建立v1和v2之间的一条边,权重为w
{
	if(G->vexlist[v1].vertex!=freever && G->vexlist[v2].vertex!=freever )   // v1和v2都为顶点
	{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(IsEdge_directed(G, v1, v2))    //判断v1与v2之间是否存在边，若存在，则删除该边
			DelSucc_directed(G, v1, v2);

		//为顶点v1到v2增加边
		p = new EdgeNode; 		
        p->adjvex = v2;				
		p->cost = w; 	
        p->next = G->vexlist[v1].firstedge;
        G->vexlist[v1].firstedge = p;		
		
		G->e++;    // 边数加1
		return true;
	}
	return false;
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
void main()
{
	/*
     cout<<"有向图:"<<endl;
	AdjGraph G1;
	IniADJGraph(&G1);
  	VertexData v1[4]={'v1', 'v2', 'v3', 'v4'};
	EdgeData e14][NumVertices]={{0, 1, 1, 0},
								{0, 0, 0, 0},
								{0, 0, 0, 1},
								{1, 0, 0, 0}};	          
	CreateADJGraph_directed(&G1, v1, e1, 4);
	cout<<G1.n<<' '<<G1.e<<endl;
	CreateADJGraph_directed(&G1);
	NewNode(&G1, 'v1');
	NewNode(&G1, 'v2');
	NewNode(&G1, 'v3');
	NewNode(&G1, 'v4');
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
	PrintADJ(&G1);
	*/
}