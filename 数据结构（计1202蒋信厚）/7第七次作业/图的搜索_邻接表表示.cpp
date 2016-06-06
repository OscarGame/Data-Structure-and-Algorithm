//邻接表表示：
//队列，深度优先搜索，广度优先搜索，拓扑排序
#include<iostream>
using namespace std;

#define freever '#'
#define NumVertices 9 			//顶点个数
typedef char VertexData; 		//顶点数据类型
typedef int EdgeData; 			//边上权值类型

typedef struct node { 			//边表结点
    int adjvex; 				//邻接点域(下标)，即下一个点的下标
    EdgeData cost; 				//边上的权值
    struct node *next; 			//下一边链接指针
} EdgeNode;

typedef struct { 				//顶点表结点
    VertexData vertex; 			//顶点数据域
    EdgeNode * firstedge; 		//边链表头指针
} VertexNode;

typedef struct { 				//图的邻接表
    VertexNode vexlist[NumVertices+1];//vexlist[0]不用
	int indegree[NumVertices+1];//顶点入度集合
    int n, e; 				//图中当前的顶点个数与边数
} AdjGraph;

void IniADJGraph(AdjGraph *G)	//初始化图					
{
	G->e=0;
	G->n=0;
	for(int i=1; i<NumVertices; i++)
	{
		G->vexlist[i].vertex=freever;
		G->vexlist[i].firstedge=NULL;
		G->indegree[i]=0;//初始化入度都为零
	}
}
bool NewNode(AdjGraph *G, VertexData v)// 增加一个顶点，不添加边，成功，返回true，否则返回false	
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
		//v1指向v2的情况
		if(p->adjvex==v2)
		{
			p1=p;
			G->vexlist[v1].firstedge=p->next;
			G->e--;
			delete p1;
			G->indegree[v2]--;//v2的入度减1
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
			G->indegree[v2]--;//v2的入度减1
		}
		//v2指向v1的情况
		p=G->vexlist[v2].firstedge;
		if(p->adjvex==v1)
		{
			p1=p;
			G->vexlist[v2].firstedge=p->next;
			delete p1;
			G->indegree[v1]--;//v1的入度减1
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
		    G->indegree[v1]--;//v2的入度减1
		}
	}
}

void DelNode(AdjGraph *G, int m)//删除第m个顶点
{

	if(G->vexlist[m].vertex!=freever)//如果第m个顶点存在
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
	for(i=1; i<=NumVertices; i++)
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
	for(i=1; i<=NumVertices; i++)
	{
		cout<<ver[i]<<'\t';
		for(j=1; j<=NumVertices; j++)
		{
			cout<<result[i][j]<<'\t';
		}
		cout<<endl;
	}
	cout<<endl;
}

//=====================================================================
//队列的指针实现

#define maxlength 20
typedef int que_elementtype;//队列元素类型

//队列元素节点类型
struct celltype {
	que_elementtype element;
	celltype *next;
};
//队列结构型
struct QUEUE {
	celltype *front;
	celltype *rear;
};
//队列基本操作
void MAKENULL( QUEUE &Q )
{
	Q.front = new celltype ;
	Q.front->next = NULL ;
	Q.rear = Q.front ;//队列为空
}

bool EMPTY( QUEUE &Q )//判断是否为空
{ 
	if ( Q.front == Q.rear )
		return true ;
	else
		return false ;
}

celltype *FRONT(QUEUE Q)//返回第一个元素节点
{
	if(Q.front==Q.rear)
		return NULL;
	else
		return Q.front->next;
}

void ENQUEUE ( que_elementtype x, QUEUE &Q )//将x插入队尾
{ 
	Q.rear->next = new celltype ;
	Q.rear = Q.rear->next ;
	Q.rear->element = x ;
	Q.rear->next = NULL ;
}

void DEQUEUE ( QUEUE &Q )//删除队列的第一个元素
{ 
	celltype *temp ;//临时元素节点
	if ( EMPTY( Q ) )
		cout<<"队列为空"<<endl ;
	else { 
		temp = Q.front->next ;
		Q.front->next = temp->next ;//表头节点指向第二个元素节点
		delete temp ;//删掉第一个元素节点
	
		if ( Q.front->next == NULL )//队列为空时将rear复位
			Q.rear = Q.front ; 
	}
}
//===============================================================
//深度优先搜索-链表表示
bool visited[NumVertices]; 	//访问标记数组是全局变量
int dfn[NumVertices]; 			//顶点的先深编号

void DFS1 (AdjGraph* G, int i);

void DFSTraverse(AdjGraph G)
//先深搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =false; 		//标志数组初始化
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS1( &G, i+1 ); //从顶点i 出发开始搜索search() DFSX(G, i )
}

void DFS1 (AdjGraph* G, int i)//以vi为出发点时对邻接表表示的图G进行先深搜索
{   
	static int count=0;
	EdgeNode *p;
    cout<<G->vexlist[i].vertex;		//访问顶点vi;
    visited[i]=true;	 			//标记vi已访问
    dfn[i]=count++; 				//对vi进行编号
    p=G->vexlist[i].firstedge; 		//取vi边表的头指针
    while( 1 )						//依次搜索vi的邻接点vj, 这里j=p->adjvex
	{ 			
        if( !visited[p->adjvex] ) 	//若vj尚未访问
            DFS1(G, p->adjvex); 	//则以vj为出发点先深搜索
        p=p->next;
		if(p==NULL)
			break;
    }	
} //DFS1

//广度优先搜索
int bfn[NumVertices]; 			//顶点的先深编号

void BFS1 (AdjGraph *G, int k)   //这里没有进行广度优先编号
{   
	int i; 
	EdgeNode *p; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ] .vertex;   
	visited[ k ] = true;
    ENQUEUE (k, Q); 			//进队列
    while ( !EMPTY (Q) ) 		//队空搜索结束
	{ 	
        i=FRONT(Q)->element;
		DEQUEUE(Q); 			//vi出队
        p =G->vexlist[ i ].firstedge; 	//取vi的边表头指针
        while ( p ) 			//若vi的邻接点vj (j= p->adjvex)存在,依次搜索
		{ 
			if (!visited[p->adjvex ])  	//若vj未访问过
			{
				cout << G->vexlist[ p->adjvex ].vertex;	//访问vj
				visited[ p->adjvex ]=true; 		//给vj作访问过标记
				ENQUEUE ( p->adjvex , Q ); 		//访问过的vj入队
        	}
            p = p->next; 	//找vi的下一个邻接点
        } 	//重复检测vi的所有邻接顶点
    } 		//外层循环，判队列空否
}			//以vk为出发点时对用邻接表表示的图G进行先广搜索

//拓扑排序
void topoOrder(AdjGraph *G)
{
	celltype *t;
	int v,w;
	int nodeCount=0;//计数拓扑节点
	QUEUE Q;
	MAKENULL(Q);
	for(v=1;v<=G->n;v++)//将所有入度为0的顶点入队
	{
		if(G->indegree[v]==0)
			ENQUEUE(v,Q);
	}

	while(!EMPTY(Q))
	{
		t = FRONT(Q);//队首出队并删除
		v=t->element;
		DEQUEUE(Q);
		cout<<v<<'\t';//拓扑过程依次输出排序的顶点
		nodeCount++;
		//搜索邻接于v的其他顶点，同样入度为零的入队
		for(w=1;w<=G->n;w++)
		{
			if(IsEdge(G,v,w))
			{
				G->indegree[w]--;
				if(G->indegree[w] == 0)
					ENQUEUE(w,Q);
			}

		}
	}
	if(nodeCount<G->n)
		cout<<"这个有向图有环路！"<<endl;

}
void main()
{
    cout<<"作业七第三题中无向图的搜索（邻接表表示）:"<<endl;
	AdjGraph G;
	IniADJGraph(&G);
	VertexData v[9]={'v1', 'v2', 'v3', 'v4', 'v5','v6','v7', 'v8','v9'};//顶点
	//EdgeData e[6][NumVertices]={{0, 1, 0, 1, 0, 1},{1, 0, 1, 1, 1, 0},{0, 1, 0, 0, 1, 0},{1, 1, 0, 0, 1, 1},{0, 1, 1, 1, 0, 0},{1, 0, 0, 1, 0, 0}};
	EdgeData e[9][NumVertices]={{0,1,1,0,0,0,0,0,0},{0,0,0,1,1,0,0,0,0},{0,0,0,0,1,1,0,0,0},{0,0,0,0,0,0,1,1,0},{0,0,0,0,0,0,0,1,1},{0,0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0}};
	CreateADJGraph(&G, v, e, 9);//创建无向图
	//PrintADJ(&G);
	//cout<<endl;
	//cout<<"深度优先搜索："<<endl;
	//DFSTraverse(G);
//	cout<<endl;
	//cout<<"广度优先搜索："<<endl;
	//BFS1(&G,0);
	cout<<"拓扑排序："<<endl;
	topoOrder(&G);
}