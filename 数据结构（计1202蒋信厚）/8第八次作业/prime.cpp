//Prime�㷨-ͼ���ڽӾ����ʾ
#include<iostream.h>

#define NumEdges 50 			//����
#define NumVertices 6 			//�������
#define MAX_TREE_ARRAY 20
#define INT_MAX 1000
typedef char elementtype_tree_array;
typedef char VertexData; 		//������������
typedef int EdgeData;			//����Ȩֵ����

typedef struct{
    VertexData vexlist[NumVertices]; 	//�����
    EdgeData edge[NumVertices][NumVertices];
            		//�ڽӾ��󡪱߱�, ����Ϊ��֮��Ĺ�ϵ
    int n;			//ͼ�е�ǰ�Ķ������
	int e; 			//ͼ�е�ǰ�ı���
} MTGraph;

void IniMGraph(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;
	G->n=0;
	G->e=0;
}

void CreateMGraph(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;

	for (i=0; i<n; i++) 			//2.���붥����Ϣ�����������
		G->vexlist[i]=V[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		//3.�ڽӾ����ʼ��
	
	for(i=0; i<n; i++)				//4.����e���߽����ڽӾ���
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

struct nodeTR
{
	int parent;
	elementtype_tree_array data;
};

typedef nodeTR TREE_ARRAY[MAX_TREE_ARRAY];
// ������T�е�n��Ԫ�ص����ֵܵ��±꣬��������ڣ��򷵻�0
int RightSibling(TREE_ARRAY T, int n)
{
	int i;
	for(i=n+1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].parent==T[n].parent)
			return i;
	}
	return 0;
}
// ������T�е�n��Ԫ�ص������ӵ��±꣬��������ڣ��򷵻�0
int LeftMostChild(TREE_ARRAY T, int n)
{
	int i;
	for(i=n+1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].parent==n)
			return i;
	}
	return 0;
}
//�ӵ�n��Ԫ�ؿ�ʼ�ȸ�������n��
void PreOrder(TREE_ARRAY T, int n)
{
	int c;
	cout<<T[n].data<<'\t';
	c=LeftMostChild(T, n);
	while(c!=0)
	{
		PreOrder(T, c);
		c=RightSibling(T, c);
	}
}
int Root(TREE_ARRAY T)
{
	int t;
	for(int i=1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].data!=' ')
		{
			t=i;
			while(1)
			{
				if(T[t].parent==0)
					return t;
				t=T[t].parent;

			}
		}

	}
}
//Prim�㷨
void Prim(MTGraph G, TREE_ARRAY T)
{   
	int i, j, k; 
	EdgeData min;//�洢��С�߳�
	EdgeData LOWCOST[NumVertices];    // �����i������δ����U����LOWCOST[i]��ʾ��i��������U�о�������Ķ���֮��ľ���
	int CLOSSET[NumVertices];  //  �����i������δ����U����LOWCOST[i]��ʾ��i��������U�о�������Ķ���
    //��ʼ��
	int n=G.n;
	for( i=1; i<n; i++ )
	{ 
		LOWCOST[i] = G.edge[0][i];  //���������붥��i֮��ľ���
		CLOSSET[i] = 0; 
		T[i+1].data=G.vexlist[i];
		T[i+1].parent=0;
	}
	T[1].data=G.vexlist[0];//������ʼ����һ������
	T[1].parent=0;
	//�ҳ�����ĵ�
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

		cout << "��"<<i<<"������ĸ��ף�"<< G.vexlist[CLOSSET[k]] <<'\t'<< "����Ķ��㣺"<<G.vexlist[k] <<"�������Ϊ��"<<G.edge[CLOSSET[k]][k]<< endl;  

		T[k].parent=CLOSSET[k];   //���������¼�����Ϊ���н��ĺ��ӽ��
		
		LOWCOST[k] = INT_MAX ;   // ��ʶ��k�������ѷ���U��

		for ( j = 1; j < n; j++ )
			if ( G.edge[k][j] < LOWCOST[j] && LOWCOST[j]!=INT_MAX)
			{   
				LOWCOST[j]=G.edge[k][j]; 
				CLOSSET[j]=k; 
			}
	}
}
//======================================================================================
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

//�����n�ĸ��ڵ�����Ϊm
void Union(TREE_ARRAY T, int m, int n)
{
	if(Find(T, m)!=Find(T, n))
		T[n].parent=m;
}

void Kruskal(MTGraph G, TREE_ARRAY T)
{	
	int i, j, k;
	// �������г�ʼ����ÿһ����㹹��һ�������丸�ڵ�Ϊ������
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
	
	// ��Ȩֵ��������
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
/*
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
*/
void main()
{
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={ 'a', 'b', 'c', 'd', 'e', 'f'};
	EdgeData e[6][6] = {
		{0,6,3,0,0,0},
		{6,0,0,1,0,5},
		{3,0,0,6,6,0},
		{0,1,6,0,0,5},
		{0,0,6,0,0,2},
		{0,5,0,5,2,0}
	};/*
	CreateMGraph(&G, v, e, 6);
	TREE_ARRAY T;
	Prim(G, T);
	PreOrder(T, 1);
	cout<<endl;
*/
	int CLOSSET[NumVertices];
	TREE_ARRAY T;
	Kruskal(G, T);
    PreOrder(T, Root(T));
	cout<<endl;
}
