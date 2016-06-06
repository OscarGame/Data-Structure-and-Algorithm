//邻接矩阵表示深度优先搜索、广度优先搜索：
#include<iostream>
using namespace std;
#define NumVertices 6//定义顶点个数

typedef char VertexData;//顶点数据类型
typedef int EdgeData;//边上权值类型

typedef struct{
 VertexData vexlist[NumVertices];//顶点数组
EdgeData edge[NumVertices][NumVertices];//邻接矩阵
int n;//定点数
int e;//边数
} MTGraph;//邻接矩阵表示的图结构，这里是无向图

void IniMGraph(MTGraph *G)//初始化邻接矩阵的图结构
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;//将所有的边删除
	G->n=0;
	G->e=0;
}

void NewNode(MTGraph *G, VertexData v)//单纯添加顶点v，不添加边
{
	G->vexlist[G->n]=v;
	G->n++;
	
}

void DelNode(MTGraph *G, int m)//删除第m个顶点
{
	int i, j;
	if(G->n==0 || m>=NumVertices)//没有顶点||不存在顶点m
		return;
	for(i=m; i<G->n-1; i++)//顶点m后面的顶点前移
		G->vexlist[i]=G->vexlist[i+1];

	//删除与第m个顶点相连的边
	//删掉边数
	for(i=0; i<G->n; i++)
	{
		if(G->edge[i][m]!=0)
			G->e--;
	}
	//邻接矩阵降阶
	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n; j++)
			G->edge[i][j]=G->edge[i+1][j];

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n-1; j++)
			G->edge[j][i]=G->edge[j][i+1];
    //减掉顶点数
	G->n--;
}
//判断v1和v2之间有没有边
bool IsEdge(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]!=0)
			return true;
		else
			return false;
	return false;
}
//在顶点v1和v2之间建立一条边
void SetSucc(MTGraph *G, int v1, int v2, EdgeData w)
{	
	if(!IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=w;	
		G->edge[v2][v1]=w;
		G->e++;
	}	
}

//删除v1和v2之间的边
void DelSucc(MTGraph *G, int v1, int v2)
{
	if(IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=0;
		G->edge[v2][v1]=0;
		G->e--;
	}	
}

//用户创建无向图
void CreateMGraph (MTGraph *G) 	
{   
	int i, j, k, w;
	cout<<"输入顶点数和边数:";
	cin>>G->n>>G->e;				

	cout<<"输入顶点的字符:";
	for (i=0; i<G->n; i++) 			
		cin>>G->vexlist[i];
    //初始化邻接矩阵
	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 
		
	for (k=0; k<G->e; k++) {		
		cout<<"输入一条边的两个顶点和边的权值: "<<endl;
		cin>>i>>j>>w;			
		G-> edge[i][j]=w;
		G-> edge[j][i]=w;
	}	
}
//后台默认直接创建
void CreateMGraph(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;
	for (i=0; i<n; i++) 			
		G->vexlist[i]=V[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		
	for(i=0; i<n; i++)				
		for(j=i; j<n; j++)
		{		
			if(E[i][j]!=0)
			{
				G-> edge[i][j]=E[i][j];
				G-> edge[j][i]=E[i][j];
				G->e++;
			}
		}
}
//显示无向图
void PrintMT(MTGraph *G)
{
	cout<<'\t';
	//输出顶点
	for(int i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';
	}
	cout<<endl;
	//输出每个顶点的连接关系
	for(i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';	
		for(int j=0; j<G->n; j++)
			cout<<G->edge[i][j]<<'\t';
		cout<<endl;
	}
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
bool visited[NumVertices];//访问标记数组是全局变量
int dfn[NumVertices]; //顶点的先深编号

void DFS2(MTGraph *G, int i);//声明

void DFSTraverse(MTGraph G)
//先深搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =false; 		//标志数组初始化，false表示new
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS2( &G, i ); //从顶点i 出发开始搜索search() DFSX(G, i )
}

void DFS2(MTGraph *G, int i)//以vi为出发点对邻接矩阵表示的图G进行深度优先搜索
{ 
    int j;
	static int count=0;
    cout<<G->vexlist[i]; 	//访问定点vi
    visited[i]=true; 	//标记vi已访问
    dfn[i]=count; 		//对vi进行编号
    count ++; 		//下一个顶点的编号
    for( j=0; j<G->n; j++) 	//依次搜索vi的邻接点
        if((G->edge[i][j] == 1) && !visited[j] ) 	//若vj尚未访问
            DFS2( G, j );
}//DFS2

//广度优先搜索
//bool visited[NumVertices]; 	//访问标记数组是全局变量
int bfn[NumVertices]; 			//顶点的先深编号

void BFS2 (MTGraph *G, int k)	//这里没有进行先广编号
{   
	int i , j; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ]; 		//访问vk
    visited[ k ] = true; 			//给vk作访问过标记
    ENQUEUE (k, Q); 				// vk进队列

    while ( ! EMPTY (Q) )			//队空时搜索结束
	{ 		
        i=FRONT(Q)->element;
		DEQUEUE(Q); 				//vi出队
        for(j=0; j<G->n; j++) { 	//依次搜索vi的邻接点vj
            if ( G->edge[ i ][ j ] ==1 && !visited[ j ]) //若vj未访问过
			{ 	
                cout << G->vexlist[ j ];		//访问vj
				visited[j]=true; 				//给vj作访问过标记
				ENQUEUE( j , Q ); 				//访问过的vj入队
            }
        } 		//重复检测vi的所有邻接顶点
    } 			//外层循环，判队列空否
} 				//以vk为出发点时对用邻接矩阵表示的图G进行先广搜索

void main()
{
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={'v1', 'v2', 'v3', 'v4', 'v5','v6'};
	EdgeData e[6][NumVertices]={{0, 1, 0, 1, 0, 1},{1, 0, 1, 1, 1, 0},{0, 1, 0, 0, 1, 0},{1, 1, 0, 0, 1, 1},{0, 1, 1, 1, 0, 0},{1, 0, 0, 1, 0, 0}};
	CreateMGraph(&G, v, e, 6);
	PrintMT(&G);
	cout<<endl;
	cout<<"深度优先搜索："<<endl;
	DFSTraverse(G);
	cout<<endl;
	cout<<"广度优先搜索："<<endl;
	BFS2(&G,1);
	cout<<endl;
}